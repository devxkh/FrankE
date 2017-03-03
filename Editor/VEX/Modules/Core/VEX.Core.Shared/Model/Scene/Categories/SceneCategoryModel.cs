#region License

//The MIT License (MIT)

//Copyright (c) 2014 Konrad Huber

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#endregion

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Controls;
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using System.Windows.Input;
using VEX.Model.Scene.Model;
using VEF.IDAL;
using VEX.Interface.Scene;
using VEX.IDAL;
using VEF.Interfaces.Services;
using VEF.Interfaces.Controls;
using VEF;
using System.Runtime.Serialization;

namespace VEX.Model.Scene
{
    [KnownType(typeof(SceneDataModel))]
    [DataContract]
    public class SceneCategoryModel : DBTableModel, IItem
    {
        public void Drop(IItem item) { }


        [Browsable(false)]
        [XmlIgnore]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();
                VEFMenuItem mib1a = new VEFMenuItem() { Header = "Create Scene", Command = new CmdCreateScene(this), CommandParameter = this };
                list.Add(mib1a);
                return list;
            }
        }

        public bool Create(IUnityContainer unityContainer) { return true; }
        public bool Open(IUnityContainer unityContainer, object id) { return true; }
        public bool Save(object param) { return true; }
        public void Refresh() { }
        public bool Delete() { return true; }

        public SceneCategoryModel()
        {
        }
    }

    public class CmdCreateScene : ICommand
    {
        private SceneCategoryModel m_model;

        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            SceneCategoryModel parent = parameter as SceneCategoryModel;

            //  sceneCategoryModel.Items.Add(new SceneCategoryModel() { Parent = sceneCategoryModel, UnityContainer = sceneCategoryModel.UnityContainer, Name = "Scene 1", ContentID = "SceneID:##:" }); //CreateScene();

            ushort id = 0;

            if (parent != null)
            {
                var tableModel = parent as DBTableModel;
                if (tableModel != null)
                {
                    id = tableModel.AutoIncrement();
                }
            }
            else
                return;

            parent.IsDirty = true;

            if (id > 0)
            {
                SceneDataModel pom = new SceneDataModel() { Parent = parent, Name = "Scene Obj NEW", ContentID = "SceneID:##:" + id, SceneID = id };

                pom.Create();
                parent.Items.Add(pom);
            }
            else
            {
                var log = VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService;
                log.Log("Error: CmdCreateScene id =  (" + id.ToString() + ")", LogCategory.Error, LogPriority.High);
            }
        }

        public CmdCreateScene(SceneCategoryModel model)
        {
            m_model = model;
        }
    }
}