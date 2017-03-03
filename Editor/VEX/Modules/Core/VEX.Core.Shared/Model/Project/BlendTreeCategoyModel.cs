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
using System.ComponentModel;
using System.Windows.Controls;
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using System.Windows.Input;
using VEX.Model.Scene.Model;
using VEX.Service.Scene;
using VEX.IDAL;
using VEX.Interface.Scene;
using VEF.Interfaces.Services;
using VEF.Interfaces.Controls;
using VEF.IDAL;
using VEF;
using VEF.Model.Services;
using VEF.Interface.History;
using VEX.Core.Shared.Service.Scene;
using NetMsg;
using VEX.Model.UI;
using System.Runtime.Serialization;
using VEX.Core.Shared.Model.Prefabs;

namespace VEX.Model.Project
{
    [KnownType(typeof(AnimationBlendTree))]
    [DataContract]
    public class BlendTreeCategoryModel : PItem
    {
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {

                List<IMenuItem> list = new List<IMenuItem>();
                VEFMenuItem miAddItem = new VEFMenuItem() { Header = "Add Item" };

                foreach (var type in CanAddThisItems)
                {
                    miAddItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddNewBlendTree(this), CommandParameter = type });
                }

                list.Add(miAddItem);
                

                //VEFMenuItem miAdd = new VEFMenuItem() { Command = new CmdCreateStaticObj(), CommandParameter = this, Header = "Create static object" };
                //menuOptions.Add(miAdd);

                return list;
            }
        }

        public override List<System.Type> CanAddThisItems
        {
            get
            {
                return new List<Type>() { typeof(AnimationBlendTree) };
            }
        }

        public BlendTreeCategoryModel()
        {
            this.Name = "BlendTreeCategoyModel";
        }

        public bool Create(IUnityContainer unityContainer) { return true; }
        public bool Open(IUnityContainer unityContainer, object id) { return true; }

        public new  bool Save(object param) 
        {
            return true; 
        }

        public void Refresh() { }
    
        public bool Delete() { return true; }
    

        //public StaticObjectCategoryModel()
        //{
        //    SceneItems = new CollectionOfISceneEntity();
        //}
    }


    public class CmdAddNewBlendTree : IHistoryCommand
    {
        private BlendTreeCategoryModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            Type t = parameter as Type;

            //if (t.Name == "VEXDBFileModel")
        //    BlendTreeCategoyModel parent = parameter as BlendTreeCategoyModel;

            UInt32 id = 0;

            if (mpm != null)
            {
                var tableModel = mpm.Parent as DBTableModel;
                if (tableModel != null)
                {
                    id = tableModel.AutoIncrement();
                }
            }

            //if (id > 0)
            //{
            //    if (t.Name == "RenderableComponent")
            //    {
            //        EntityX newEntity = new EntityX() {  Name = "New Entity" };
            //        RenderableComponent pom = new RenderableComponent() { Parent = newEntity };
              

            //      //  pom.Create();
            //        mpm.Items.Add(newEntity); 
            //        newEntity.Components.Add(pom);
            //    }

                if (t.Name == "AnimationBlendTree")
                {
                // EntityX newEntity = new EntityX() { Name = "New Entity" };
                AnimationBlendTree pom = new AnimationBlendTree();// { Parent = newEntity };
                  
                  //  pom.Create();
                    mpm.Items.Add(pom);
                  //  newEntity.Components.Add(pom);

                }
            //}
            //else
            //{
            //    (VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService).Log("Error: CmdCreateStaticObj id =  (" + id.ToString() + ")", LogCategory.Error, LogPriority.High);
            //}
        }

        public CmdAddNewBlendTree(BlendTreeCategoryModel pm)
        {
            mpm = pm;
        }

        public bool CanRedo() { return true; }
        public bool CanUndo() { return true; }
        public void Redo() { }
        public string ShortMessage() { return "add item"; }
        public void Undo() { }

    }
}