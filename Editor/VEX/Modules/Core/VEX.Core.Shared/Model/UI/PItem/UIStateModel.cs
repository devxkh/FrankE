using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Text;
using System.Windows.Input;
using System.Xml.Serialization;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEX.Core.Model;
using VEX.Core.Shared.Model.UI.FBufferObject;
using VEX.Interface.DAL;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Shared.Model.UI
{
    [DataContract(IsReference = true)]
    public class UIStateModel : PItem 
    {
        private SourceItem _SourceItem;
        
        public bool Watch { get; set; }

        #region INETID


        [Browsable(false)]
        private IFBObject FBObject { get; set; } 

        [ExpandableObject]
        [DataMember]
        public FB_UI_State FB_UI_State { get { return FBObject as FB_UI_State; } set { FBObject = value; } }
        
        #endregion
        

        [XmlIgnore]
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

                list.Add(new VEFMenuItem() { Header = "Generate FB File", Command = new CmdGenAtlasFile(this) });

                return list;
            }
        }

        public UIStateModel()
        {
            Name = typeof(UIStateModel).Name;
            FBObject = new FB_UI_State();
        }
    }

    public class CmdGenAtlasFile : ICommand
    {
        private UIStateModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            var fbData = mpm.FB_UI_State.CreateFBData();

            //using (FileStream fileStream = new FileStream(@"F:\Projekte\coop\XGame\data\dbData\UI\TestAtlas.fbbin", FileMode.Create))
            //{
            //    // Write the data to the file, byte by byte.
            //    for (int i = 0; i < fbData._fbData.Length; i++)
            //    {
            //        fileStream.WriteByte(fbData._fbData[i]);
            //    }

            //    // Set the stream position to the beginning of the file.
            //    fileStream.Seek(0, SeekOrigin.Begin);

            //    // Read and verify the data.
            //    for (int i = 0; i < fileStream.Length; i++)
            //    {
            //        if (fbData._fbData[i] != fileStream.ReadByte())
            //        {
            //            Console.WriteLine("Error writing data.");
            //            return;
            //        }
            //    }
            //    Console.WriteLine("The data was written to {0} " +
            //        "and verified.", fileStream.Name);

            //}
        }

        public CmdGenAtlasFile(UIStateModel pm)
        {
            mpm = pm;
        }
    }

    
}
