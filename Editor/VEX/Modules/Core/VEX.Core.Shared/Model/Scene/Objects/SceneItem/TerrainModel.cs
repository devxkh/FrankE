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
using System.Linq;
using System.Windows.Controls;
using Microsoft.Practices.Unity;
using VEX.Service.Scene;
using VEF.Interfaces.Services;
using VEX.Interface.Scene;
using VEF.Core.Helper;

namespace VEX.Model.Scene.Model
{
    //public class TerrainModel : EntityX
    //{
    //    public IItem Parent { get; set; }
    //    public bool Visible { get; set; }
    //    public bool Enabled { get; set; }

    //    public void Drop(IItem item) { }

    //    public string ContentID { get; set; }
      
    //    public Int32 ID { get; protected set; }
    //    public string Name { get; set; }
    //    public Int32 NodeID { get; set; }
      
    //    //public CollectionOfISceneEntity SceneItems { get; private set; }
    //    [Browsable(false)]
    //    public CollectionOfIItem Items { get; private set; }
    //    [Browsable(false)]
    //    public List<MenuItem> MenuOptions
    //    {
    //        get
    //        {
    //            List<MenuItem> list = new List<MenuItem>();
    //            MenuItem miSave = new MenuItem() {  Header = "Save" };
    //            list.Add(miSave);
    //            return list;
    //        }
    //    }

    //    public bool Create(IUnityContainer unityContainer) { return true; }
    //    public bool Open(IUnityContainer unityContainer, object id) { return true; }
    //    public bool Save(object param) { return true; }
    //    public void Refresh() { }
    //    public void Finish() { }
    //    public bool Delete() { return true; }
    //    public bool Closing() { return true; }

    //    [Browsable(false)]
    //    public bool IsExpanded { get; set; }
    //    [Browsable(false)]
    //    public bool IsSelected { get; set; }
    //  //  public bool HasChildren { get { return SceneItems != null && SceneItems.Count > 0 ? true : false; } }

    //    public IUnityContainer UnityContainer { get; set; }
    //    public TreeNode TreeNode { get; set; }

    //    public TerrainModel(IEntity parent,IUnityContainer unityContainer )
    //    {
    //        UnityContainer = unityContainer;
    //        Parent = parent;
    // //       SceneItems = new CollectionOfISceneEntity();
    //    //    parent.SceneItems.Add(this);
    //    }

    //}
}
