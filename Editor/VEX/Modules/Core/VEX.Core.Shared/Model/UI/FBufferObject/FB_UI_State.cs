using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.Serialization;
using System.Text;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Shared.Model.UI.FBufferObject
{
    [DataContract]
    public struct Align
    {
        [DataMember]
        public float vertical { get; set; }        // 0.0(top) - 1.0(bottom) 

        [DataMember]
        public float horizontal { get; set; }      // 0.0(left) - 1.0(right) 
    }

    [DataContract]
    public struct Scale
    {
        [DataMember]
        public float vertical { get; set; }        // 0.0(minreq) - 1.0(stretch) 

        [DataMember]
        public float horizontal { get; set; }  // 0.0(minreq) - 1.0(stretch) 
    }

    [DataContract]
    public class GradientParam
    {
        [DataMember]
        public System.Windows.Media.Color colour { get; set; }

        [DataMember]
        public ushort offset { get; set; }

        public GradientParam()
        {
            colour = new System.Windows.Media.Color();
        }
    }

    [DataContract]
    public class Gradient
    {
        [DataMember]
        [ExpandableObject]
        public XFB_UI.GradientType gradientType { get; set; }

        [DataMember]
        [ExpandableObject]
        public GradientParam sart { get; set; }

        [DataMember]
        [ExpandableObject]
        public GradientParam stop { get; set; }

        public Gradient()
        {
            sart = new GradientParam();
            stop = new GradientParam();
        }
    }

    [DataContract]
    public struct Padding
    {
        [DataMember]
        public ushort l { get; set; }

        [DataMember]
        public ushort t { get; set; }

        [DataMember]
        public ushort r { get; set; }

        [DataMember]
        public ushort b { get; set; }
    }

    [DataContract]
    public struct Margin
    {
        [DataMember]
        public ushort l { get; set; }

        [DataMember]
        public ushort t { get; set; }

        [DataMember]
        public ushort r { get; set; }

        [DataMember]
        public ushort b { get; set; }
    }

    [DataContract]
    public struct Thickness
    {
        [DataMember]
        public ushort l { get; set; }

        [DataMember]
        public ushort t { get; set; }

        [DataMember]
        public ushort r { get; set; }

        [DataMember]
        public ushort b { get; set; }
    }

    [DataContract]
    public class WidgetState
    {
        [DataMember]
        public string bgImage { get; set; }       //image name from atlas

        [DataMember]
        [ExpandableObject]
        public Gradient bgGradient { get; set; }

        [DataMember]
        public bool bgAnimated { get; set; }

        [DataMember]
        public Color bgColour { get; set; }

        [DataMember]
        public Color colour { get; set; }

        [DataMember]
        [ExpandableObject]
        public Padding border { get; set; }

        [DataMember]
        public uint fontsize { get; set; }

        public WidgetState()
        {
            bgGradient = new Gradient();
            border = new Padding();
            bgColour = new Color();
            colour = new Color();
        }
    }

    [DataContract]
    public class Style
    {
        [DataMember]
        public string name { get; set; }                    //style name -> for specific styles e.g. exit button is red

        [DataMember]
        public XFB_UI.StyleType type { get; set; }            //tyle type -> sets all elements from this type automaticly

        [DataMember]
        [ExpandableObject]
        public WidgetState normalState { get; set; }       // Normal

        [DataMember]
        [ExpandableObject]
        public WidgetState activeState { get; set; }       // Active, e.g. when a button is pressed

        [DataMember]
        [ExpandableObject]
        public WidgetState prelightState { get; set; }      // Prelight, e.g. when the mouse moves over a widget. 

        [DataMember]
        [ExpandableObject]
        public WidgetState selectedState { get; set; }      // Selected, e.g. when a list item in a list is selected. 

        [DataMember]
        [ExpandableObject]
        public WidgetState insensitiveState { get; set; }   // Insensitive, disabled widget. 

        [DataMember]
        [ExpandableObject]
        public Scale scale { get; set; }                   // width,height,stretched

        [DataMember]
        [ExpandableObject]
        public Margin margin { get; set; }

        public Style()
        {
            normalState = new WidgetState();
            prelightState = new WidgetState();
            prelightState = new WidgetState();
            selectedState = new WidgetState();
            insensitiveState = new WidgetState();
            scale = new Scale();
            margin = new Margin();
        }
    }

    [KnownType(typeof(Style))]
    [DataContract]
    public class UI_StyleData
    {
        [DataMember]
        public ObservableCollection<Style> styles { get; set; }

        public UI_StyleData()
        {
            styles = new ObservableCollection<Style>();
        }
    }


    //-------------- Base for all widgets ------------------

    [DataContract(IsReference = true)]
    public class Element
    {
        [DataMember]
        public string name { get; set; }
        [DataMember]
        public ushort id { get; set; }
        [DataMember]
        [ExpandableObject]
        public Align align { get; set; }
        [DataMember]
        [ExpandableObject]
        public Scale scale { get; set; }
        [DataMember]
        [ExpandableObject]
        public Helper.Vector2 positon { get; set; }         //overrides alignment
        [DataMember]
        public uint width { get; set; }
        [DataMember]
        public uint height { get; set; }
        [DataMember]
        public ushort rotation { get; set; }
        [DataMember]
        public string tooltip { get; set; }
        [DataMember]
        public string atlas { get; set; }
        [DataMember]
        public ushort group { get; set; }
        [DataMember]
        public bool isEnabled { get; set; }
        [DataMember]
        [ExpandableObject]
        public Style style { get; set; }           //explicit style setting

        public Element()
        {
            style = new Style();
            positon = new Helper.Vector2();
            scale = new Scale();
            align = new Align();
        }
    }

    //-------------- Widgets ------------------

    [DataContract(IsReference = true)]
    public class Label : Element
    {
        [DataMember]
        public ushort fontSize { get; set; }
    }


    [DataContract(IsReference = true)]
    public class Image : Element
    {

    }

    [DataContract(IsReference = true)]
    public class Button : Element
    {
        [DataMember]
        public string image { get; set; }

        [DataMember]
        public string itemsource { get; set; }      //Splitbutton -> binding to list in c++

        [DataMember]
        public string onclicked { get; set; }

        [DataMember]
        public string onhover { get; set; }
    }

    [DataContract(IsReference = true)]
    public class UI_ProgressBar : Element
    {        
    }

    [DataContract(IsReference = true)]
    public class UI_Box : Element
    {
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [NewItemTypes(new Type[] {  typeof(UI_Alignment),
                typeof(UI_Box),
                typeof(UI_ProgressBar),
                typeof(Button),
                typeof(Image),
                typeof(Label)})]
        [DataMember]
        public ObservableCollection<Element> uiElements { get; set; }

        [DataMember]
        [ExpandableObject]
        public XFB_UI.Orientation orientation { get; set; }

        public UI_Box()
        {
            uiElements = new ObservableCollection<Element>();
            orientation = new XFB_UI.Orientation();
        }
    }

    [KnownType(typeof(Element))]
    [DataContract(IsReference = true)]
    public class UI_Alignment : Element
    {
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [NewItemTypes(new Type[] {  typeof(UI_Alignment),
                typeof(UI_Box),
                typeof(UI_ProgressBar),
                typeof(Button),
                typeof(Image),
                typeof(Label)})]
        [DataMember]
        public ObservableCollection<Element> uiElements { get; set; }

        public UI_Alignment()
        {
            uiElements = new ObservableCollection<Element>();
        }
    }

    [KnownType("GetKnownTypes")]
    [DataContract]
    public class FB_UI_State : IFBObject//, INetMsg
    {
        static IEnumerable<Type> GetKnownTypes()
        {
            return new Type[]
             {
                typeof(Element),
                typeof(UI_Alignment),
                typeof(UI_Box),
                typeof(UI_ProgressBar),
                typeof(Button),
                typeof(Image),
                typeof(Label),
              };
        }

        #region private members

        // private XFBType.Node m_FBData = new XFBType.Node();

        private ObservableCollection<SpriteModel> _sprites;
        private ObservableCollection<Element> _elements;

        #endregion

        #region Properties

        [DataMember]
        public string atlas { get; set; }              //load atlas on demand -> only if not already loaded
        [DataMember]
        public bool autoDeleteAtlas { get; set; }      //true = delete atlas if state is destructed, else atlas won't be deleted
                                                       //locations:[ResourceLocation];

        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [NewItemTypes(new Type[] {  typeof(UI_Alignment),
                typeof(UI_Box),
                typeof(UI_ProgressBar),
                typeof(Button),
                typeof(Image),
                typeof(Label)})]
        [DataMember]
        public ObservableCollection<Element> elements { get { return _elements; } set { _elements = value; } }

    //    [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
    //    public ObservableCollection<SpriteModel> Sprites { get { return _sprites; } }

        //   public NetMsg.Data FBMsgType { get { return NetMsg.Data.Node; } }

        public object Parent { get; set; }

        public string AbsPathToXML { get; set; }
        public string RelPathToXML { get; set; }

        #endregion

        public FB_UI_State()
        {
            _sprites = new ObservableCollection<SpriteModel>();
            _elements = new ObservableCollection<Element>();
        }

        #region Methods 

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
       //     m_FBData = XFBType.Node.GetRootAsNode(byteBuffer); // read 

            //m_Rotation = new Quaternion() { W = m_FBData.Transform.Rot.W, X = m_FBData.Transform.Rot.X, Y = m_FBData.Transform.Rot.Y, Z = m_FBData.Transform.Rot.Z };
            //m_Location = new Vector3() { X = m_FBData.Transform.Loc.X, Y = m_FBData.Transform.Loc.Y, Z = m_FBData.Transform.Loc.Z };
            //m_Scale = new Vector3() { X = m_FBData.Transform.Scl.X, Y = m_FBData.Transform.Scl.Y, Z = m_FBData.Transform.Scl.Z };
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            VectorOffset spritesOffset = new VectorOffset();
            if (_sprites.Count > 0)
            {
                List<int> spriteOffsets = new List<int>();
                foreach (var sprite in _sprites)
                    spriteOffsets.Add(XFBType.Sprite.CreateSprite(fbb, sprite.width, sprite.height, sprite.posX, sprite.posY, fbb.CreateString(sprite.Name ?? "")).Value);

                XFBType.Atlas.StartSpritesVector(fbb, _sprites.Count);
                foreach (var sprite in spriteOffsets)
                    fbb.AddOffset(sprite);
                spritesOffset = fbb.EndVector();
            }

            XFBType.Atlas.StartAtlas(fbb);
            XFBType.Atlas.AddSprites(fbb, spritesOffset);

            var finishOffset = XFBType.Atlas.EndAtlas(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }

        #endregion
    }
}
