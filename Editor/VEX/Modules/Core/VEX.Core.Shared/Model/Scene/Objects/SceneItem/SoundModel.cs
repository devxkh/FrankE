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
using VEF.Interfaces.Services;
using VEX.Interface.Scene;
using VEX.Service.Scene;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Model.Scene.Model
{
    //public class SoundModel : EntityX
    //{
    //     public bool Visible { get; set; }
    //    public bool Enabled { get; set; }

    //    public string ContentID { get; set; }

    //    //[XmlIgnore]
    //    //[Browsable(false)]
    //    //public CollectionOfISceneEntity SceneItems { get; private set; }

    //    //[XmlIgnore]
    //    //[ExpandableObject]
    //    //public ProtoType.Node Node { get; set; }

    //    //[XmlIgnore]
    //    //[Browsable(false)]
    //    //public MDB.SceneNodes SceneNode { get; private set; }


    //    public string Name { get; set; }


    //    [Browsable(false)]
    //    public CollectionOfIItem Items { get; set; }

    //    //[XmlIgnore]
    //    //private ProtoType.Camera mData;

    //    //[XmlIgnore]
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
    //    public List<MenuItem> MenuOptions
    //    {
    //        get
    //        {
    //            List<MenuItem> list = new List<MenuItem>();
    //            MenuItem miSave = new MenuItem() { Header = "Save" };
    //            list.Add(miSave);
    //            return list;
    //        }
    //    }


    //    [Browsable(false)]
    //    public bool IsExpanded { get; set; }

    //    [Browsable(false)]
    //    public bool IsSelected { get; set; }

    //    //[XmlIgnore]
    //    //[Browsable(false)]
    //    //public bool HasChildren { get { return SceneItems != null && SceneItems.Count > 0 ? true : false; } }

    //    [XmlIgnore]
    //    [Browsable(false)]
    //    public IItem Parent { get; set; }

    //    public bool Open()
    //    {

    //        //todo ! from db
    //        // SceneNodes = new SceneNodes() { NodeID = sNode.NodeID, EntID = sNode.Node.EntityID, SceneID = ID, Data = ProtoSerialize.Serialize(sNode.Node) };

    //        return true;
    //    }

    //    public bool Create() { return true; }
    //    public bool Save() { return true; }
    //    public bool Delete() { return true; }

    //    /// <summary>
    //    /// default constructor for serialization
    //    /// </summary>
    //    public SoundModel()
    //    {

    //    }

    //    public SoundModel(IItem parent)
    //    {
    //        Items = new CollectionOfIItem();
    //    }
    //}
}