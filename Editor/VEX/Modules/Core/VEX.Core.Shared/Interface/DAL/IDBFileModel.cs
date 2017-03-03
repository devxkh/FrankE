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
using VEF.Interfaces.Services;
using System.Windows;

namespace VEX.IDAL
{

    public interface IDBFileModel :  IItem , IDBFileItem
    {
        string DBFilePath { get; set; }

      

        //public string Name { get; set; }
        //public CollectionOfIItem Items { get; set; }

        //public string ContentID { get; set; }

        //public void Drop(IItem item) { }

        //[Browsable(false)]
        //[XmlIgnore]
        //public List<MenuItem> MenuOptions { get; protected set; }

        //public bool IsExpanded { get; set; }
        //public bool IsSelected { get; set; }
        //public bool Enabled { get; set; }
        //public bool Visible { get; set; }

        //[Browsable(false)]
        //[XmlIgnore]
        //public bool HasChildren { get { return Items != null && Items.Count > 0 ? true : false; } }

        //[Browsable(false)]
        //[XmlIgnore]
        //public IItem Parent { get; set; }

        //public bool Create() { return true; }
        //public bool Open(object id) { return true; }
        //public bool Save(object param) { return true; }
        //public bool Delete() { return true; }
        //public bool Closing() { return true; }
        //public void Refresh() { }
        //public void Finish() { }


        //public DBFileModel()
        //{

        //}

        //[Browsable(false)]
        //[XmlIgnore]
        //public IUnityContainer UnityContainer { get; private set; }

        //public DBFileModel(IItem parent, IUnityContainer unityContainer)
        //{
        //    UnityContainer = unityContainer;
        //    Parent = parent;
        //    Items = new CollectionOfIItem();
        //    MenuOptions = new List<MenuItem>();

        //    MenuItem mib1a = new MenuItem();
        //    mib1a.Header = "Text.xaml";
        //    MenuOptions.Add(mib1a);

        //}
    }

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
}