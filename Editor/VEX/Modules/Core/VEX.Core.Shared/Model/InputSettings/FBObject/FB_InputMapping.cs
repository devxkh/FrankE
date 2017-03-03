using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;
using System.Text;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Model.InputSettings.FBObject
{
    [DataContract]
    public class InputEvent
    {
        [DataMember]
        public ControllerSettings.EventType EventType { get; set; }

        [DataMember]
        public ControllerSettings.ActionOperator ActionOperator { get; set; }

        [DataMember]
        public ControllerSettings.KeyID KeyCode { get; set; }

        [DataMember]
        public ControllerSettings.MouseBottonID MouseButtonID { get; set; }

        [DataMember]
        public ControllerSettings.MouseWheelEvent MouseWheelEvent { get; set; }

        [DataMember]
        public ushort JoyAxis { get; set; }

        [DataMember]
        public short JoyBtn { get; set; }
    }

    [DataContract]
    public class InputAction
    {
        [DataMember]
        public ControllerSettings.ActionType ActionType { get; set; }


        [DataMember]
        public ObservableCollection<InputEvent> Events { get; set; }

        public InputAction()
        {
            Events = new ObservableCollection<InputEvent>();
        }
    }

    [DataContract]
    public class InputController
    {
        [DataMember]
        public ControllerSettings.DeviceType DeviceType { get; set; }

        [DataMember]
        public ObservableCollection<InputAction> InputActions { get; set; }

        public InputController()
        {
            InputActions = new ObservableCollection<InputAction>();
        }
    }

    [DataContract]
    public class FB_InputMapping
    {
        #region Graphics

        [DataMember]
        public ObservableCollection<InputController> InputControllers { get; set; }
        
        #endregion
        
        public FB_InputMapping()
        {
            InputControllers = new ObservableCollection<InputController>();
        }

        #region Methods 

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
            var  tmp = ControllerSettings.ControllerList.GetRootAsControllerList(byteBuffer); // read 
            var ctrlList = tmp.GetCtrlList(0);
          
            //m_Rotation = new Quaternion() { W = m_FBData.Transform.Rot.W, X = m_FBData.Transform.Rot.X, Y = m_FBData.Transform.Rot.Y, Z = m_FBData.Transform.Rot.Z };
            //m_Location = new Vector3() { X = m_FBData.Transform.Loc.X, Y = m_FBData.Transform.Loc.Y, Z = m_FBData.Transform.Loc.Z };
            //m_Scale = new Vector3() { X = m_FBData.Transform.Scl.X, Y = m_FBData.Transform.Scl.Y, Z = m_FBData.Transform.Scl.Z };
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            VectorOffset inputControllersVectorOffset = new VectorOffset();
            if (InputControllers.Count > 0)
            {
                List<int> inputControllersOffsets = new List<int>();
                //------------ controller ----------------
                foreach (var controller in InputControllers)
                {
                    //------------ Actions ------------
                    VectorOffset inputActionsVectorOffset = new VectorOffset();
                    if (controller.InputActions.Count > 0)
                    {
                        List<int> inputActionsOffsets = new List<int>();
                        foreach (var action in controller.InputActions)
                        {
                            //-------------------- Events ---------------
                            VectorOffset inputEventsVectorOffset = new VectorOffset();
                            if (action.Events.Count > 0)
                            {
                                List<int> inputEventsOffsets = new List<int>();
                                foreach (var inputEvent in action.Events)
                                {
                                    inputEventsOffsets.Add(ControllerSettings.Event.CreateEvent(fbb, inputEvent.EventType, inputEvent.ActionOperator,
                                        inputEvent.KeyCode, inputEvent.MouseButtonID, inputEvent.MouseWheelEvent, inputEvent.JoyAxis, inputEvent.JoyBtn).Value);
                                }

                                ControllerSettings.Action.StartEventsVector(fbb, action.Events.Count);
                                foreach (var inputEvent in inputEventsOffsets)
                                    fbb.AddOffset(inputEvent);
                                inputEventsVectorOffset = fbb.EndVector();
                            }
                            //------------------------------------------------

                            inputActionsOffsets.Add(ControllerSettings.Action.CreateAction(fbb, action.ActionType, inputEventsVectorOffset).Value);
                        }

                        ControllerSettings.ControllerMap.StartActionMapVector(fbb, inputActionsOffsets.Count);
                        foreach (var action in inputActionsOffsets)
                            fbb.AddOffset(action);
                        inputActionsVectorOffset = fbb.EndVector();
                    }

                    inputControllersOffsets.Add(ControllerSettings.ControllerMap.CreateControllerMap(fbb, controller.DeviceType, inputActionsVectorOffset).Value);
                }

                ControllerSettings.ControllerList.StartCtrlListVector(fbb, InputControllers.Count);
                foreach (var inputCtrl in inputControllersOffsets)
                    fbb.AddOffset(inputCtrl);
                inputControllersVectorOffset = fbb.EndVector();

                ControllerSettings.ControllerList.StartControllerList(fbb);
                ControllerSettings.ControllerList.AddCtrlList(fbb, inputControllersVectorOffset);
                var finishOffset = ControllerSettings.ControllerList.EndControllerList(fbb);

                fbb.Finish(finishOffset.Value); //!!!!! important ..
                return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
            }
            return new FBNetData();
        }

        #endregion
    }
}
