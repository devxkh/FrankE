using Module.PFExplorer.Service;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Runtime.Serialization;
using System.Text;
using System.Windows;
using System.Windows.Input;
using VEF;
using VEF.Core.Model.Services;
using VEF.DAL.Interface;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.View.Types;
using VEX.Core.Shared.Model.InputSettings.FBObject;
using VEX.IDAL;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Shared.Model.InputSettings
{
    public class DBFileUtil
    {
        public static string GetDBFilePath(IItem item)
        {
            var dbFile = item as IDBFileModel;
            if (dbFile != null)
            {
                if (dbFile.DBFilePath == null)
                    MessageBox.Show("Info: No DBFilePath is set!");
                return dbFile.DBFilePath;
            }
            //else if (item.Parent != null)
            //{
            return GetDBFilePath(item.Parent);
            //}else
            //{
            //    return null;
            //}
        }
    }

    [DataContract(IsReference = true)]
    public class VEXSettings : ProjectItemModel
    {
        [Editor(typeof(FolderEditor), typeof(FolderEditor))]
        [DataMember]
        [Description("Rootfolder where the game data files are located")] //e.g. F:\\Projekte\\coop\\XGame\\data\
        public string DataRootFolder { get; set; }

        [ExpandableObject]
        [DataMember]
        public FB_Settings FB_Settings { get; set; }

        [ExpandableObject]
        [DataMember]
        public FB_InputMapping FB_InputMapping { get; set; }

        public VEXSettings()
        {
            FB_Settings = new FB_Settings();
            FB_InputMapping = new FB_InputMapping();
        }

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

                list.Add(new VEFMenuItem() { Header = "Gen Flatbuffer files", Command = new CmdGenFBFiles(this) });

                return list;
            }
        }

        public bool SaveToFile()
        {
            try {
                var settings = FB_Settings.CreateFBData();

                FB_Settings.Read(settings._fbData); //test

                var inputMapping = FB_InputMapping.CreateFBData();

                FB_InputMapping.Read(inputMapping._fbData); //test

                if (settings._fbData != null)
                {
                    using (FileStream fileStream = new FileStream(DataRootFolder + "\\settings.fbbin", FileMode.Create))
                    {
                        fileStream.Write(settings._fbData, 0, settings._fbData.Length);

                        //// Write the data to the file, byte by byte.
                        //for (int i = 0; i < settings._fbData.Length; i++)
                        //{
                        //    fileStream.WriteByte(settings._fbData[i]);
                        //}

                        // Set the stream position to the beginning of the file.
                        fileStream.Seek(0, SeekOrigin.Begin);

                        // Read and verify the data.
                        for (int i = 0; i < fileStream.Length; i++)
                        {
                            if (settings._fbData[i] != fileStream.ReadByte())
                            {
                                Console.WriteLine("Error writing data.");
                                return false;
                            }
                        }
                        Console.WriteLine("The settings data was written to {0} " + "and verified.", fileStream.Name);
                    }
                }

                if (inputMapping._fbData != null)
                {
                    using (FileStream fileStream = new FileStream(DataRootFolder + "\\inputMap.fbbin", FileMode.Create))
                    {
                        fileStream.Write(inputMapping._fbData, 0, inputMapping._fbData.Length);

                        //// Write the data to the file, byte by byte.
                        //for (int i = 0; i < settings._fbData.Length; i++)
                        //{
                        //    fileStream.WriteByte(settings._fbData[i]);
                        //}

                        // Set the stream position to the beginning of the file.
                        fileStream.Seek(0, SeekOrigin.Begin);

                        // Read and verify the data.
                        for (int i = 0; i < fileStream.Length; i++)
                        {
                            if (inputMapping._fbData[i] != fileStream.ReadByte())
                            {
                                Console.WriteLine("Error writing data.");
                                return false;
                            }
                        }
                        Console.WriteLine("The inputMapping data was written to {0} " + "and verified.", fileStream.Name);
                    }
                }
            }catch(Exception ex)
            {
                var test = VEFModule.UnityContainer.Resolve(typeof(LoggerService),"") as LoggerService;
                test.Log(ex.Message, LogCategory.Exception, LogPriority.Medium);
            }

            return true;
        }
    }

    public class CmdGenFBFiles : ICommand
    {
        private VEXSettings mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            mpm.SaveToFile();
        }

        public CmdGenFBFiles(VEXSettings pm)
        {
            mpm = pm;
        }
    }
}
