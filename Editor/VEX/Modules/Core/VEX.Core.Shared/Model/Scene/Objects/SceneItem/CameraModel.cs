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
using Microsoft.Practices.Unity;
using System.Xml.Serialization;
using VEX.Service.Scene;
using VEF.Interfaces.Services;
using VEF.Interfaces.Controls;

namespace VEX.Model.Scene.Model
{
    //public class CameraModel : EntityX
    //{
      
    //    public void Drop(IItem item) { }
   
    //    //[XmlIgnore]
    //    //private ProtoType.Camera mData;

    //    //[Category("Conections")]
    //    //[Description("This property is a complex property and has no default editor.")]
    //    //[ExpandableObject]
    //    //public ProtoType.Camera Data
    //    //{
    //    //    get
    //    //    {
    //    //        return mData;
    //    //    }
    //    //    set { mData = value; }
    //    //}

    //    [XmlIgnore]
    //    [Browsable(false)]
    //    public override List<IMenuItem> MenuOptions
    //    {
    //        get
    //        {
    //            List<IMenuItem> list = new List<IMenuItem>();
    //            VEFMenuItem miSave = new VEFMenuItem() { Header = "Save" };
    //            list.Add(miSave);
    //            return list;
    //        }
    //    }
 
    //    public bool Open(IUnityContainer unityContainer,object id)
    //    {

    //        //todo ! from db
    //       // SceneNodes = new SceneNodes() { NodeID = sNode.NodeID, EntID = sNode.Node.EntityID, SceneID = ID, Data = ProtoSerialize.Serialize(sNode.Node) };
                        
    //        return true; }
      
    //    public bool Create(IUnityContainer unityContainer) { return true; }
    //    public bool Save( object param) { return true; }
    //    public void Refresh() { }
    //   public bool Delete() { return true; }
      
    //}
}
