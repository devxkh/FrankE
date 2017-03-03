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
using VEF.Model.Services;
using VEF.Interfaces.Services;
using System.Runtime.Serialization;
using VEX.Model.Scene;
using VEX.Model.Project;
using VEF.Interfaces.Controls;
using VEF.Interface.History;
using VEX.Service.Scene;
using VEX.IDAL;
using VEF.DAL.Interface;

namespace VEF.IDAL
{
   // [KnownType(typeof(EntityCategoryModel))]
    [DataContract(IsReference = true)]
    public class DBEntitiesModel: DBTableModel, IDBFileItem
    {
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {

                List<IMenuItem> list = new List<IMenuItem>();
                VEFMenuItem miAddItem = new VEFMenuItem() { Header = "Add Entity", Command = new CmdAddEntityWithComponent(this) };

                //foreach (var type in CanAddThisItems)
                //{
                //    miAddItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddEntityWithComponent(this), CommandParameter = type });
                //}

                list.Add(miAddItem);


                //VEFMenuItem miAdd = new VEFMenuItem() { Command = new CmdCreateStaticObj(), CommandParameter = this, Header = "Create static object" };
                //menuOptions.Add(miAdd);

                return list;
            }
        }

        public bool SaveToDB(IDAL_DCTX ctx)
        {
            string DBPath = DBFileUtil.GetDBFilePath(this.Parent);
            if (!String.IsNullOrEmpty(DBPath))
            {
                foreach (var item in Items)
                {
                    var entity = item as EntityX;
                    if (entity != null)
                    {
                        entity.SaveToDB(ctx);  
                    }
                }

            }
            return true;

        }


        public class CmdAddEntityWithComponent : IHistoryCommand
        {
            private DBEntitiesModel mpm;
            public event EventHandler CanExecuteChanged;

            public bool CanExecute(object parameter)
            {
                return true;
            }

            public void Execute(object parameter)
            {
                Type t = parameter as Type;


                EntityX newEntity = new EntityX() { Name = "New Entity" };
                newEntity.EntityID = (uint)mpm.Items.Count + 1;
                newEntity.Parent = mpm;
                mpm.Items.Add(newEntity);
                
                //    (VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService).Log("Error: CmdCreateStaticObj id =  (" + id.ToString() + ")", LogCategory.Error, LogPriority.High);

            }

            public CmdAddEntityWithComponent(DBEntitiesModel pm)
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
}