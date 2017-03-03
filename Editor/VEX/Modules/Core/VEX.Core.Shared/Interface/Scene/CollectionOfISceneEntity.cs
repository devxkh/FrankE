using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;
using VEX.Interface.Scene;

namespace VEX.Interface.Scene
{
   // [Serializable]
    //public class CollectionOfISceneEntity : ObservableCollection<IEntityComponent>, IXmlSerializable
    //{
    //    public CollectionOfISceneEntity() : base() { }

    //    public System.Xml.Schema.XmlSchema GetSchema() { return null; }

    //    public void ReadXml(XmlReader reader)
    //    {
    //        try
    //        {
    //            bool isMainEmptyElement = reader.IsEmptyElement; // (1)http://www.codeproject.com/Articles/43237/How-to-Implement-IXmlSerializable-Correctly

    //            reader.ReadStartElement("Entities");

    //            if (!isMainEmptyElement)
    //            {
    //                while (reader.IsStartElement("IEntityComponent"))
    //                {
    //                    Type type = Type.GetType(reader.GetAttribute("AssemblyQualifiedName"));
    //                    XmlSerializer serial = new XmlSerializer(type);

    //                    bool isEmptyElement = reader.IsEmptyElement; // (1)


    //                    reader.ReadStartElement("IEntityComponent");

    //                    if (!isEmptyElement)
    //                    {
    //                        var item = (IEntityComponent)serial.Deserialize(reader);
    //                        this.Add(item);


    //                        reader.ReadEndElement();
    //                    }
    //                }

    //                reader.ReadEndElement();
    //            }
    //        }
    //        catch (Exception ex)
    //        {

    //        }
    //    }

    //    //public int SomeSortOfUniqueID
    //    //{
    //    //    get
    //    //    {
    //    //        //guess what this property has to do!
    //    //    }
    //    //}

    //    //public void WriteXml(XmlWriter writer)
    //    //{
    //    //    WriteXml(writer, new HashSet<ISceneItem>());
    //    //}
    //    //private void WriteXml(XmlWriter writer, HashSet<ISceneItem> alreadyWritten)
    //    //{
    //    //    if (alreadyWritten.Add(this))
    //    //    {
    //    //        writer.WriteStartElement("ISceneItem");
    //    //        writer.WriteAttributeString("uniqueID", SomeSortOfUniqueID.ToString());
    //    //        //More stuff here.
    //    //        foreach (ISceneItem contained in this)
    //    //            contained.WriteXml(writer, alreadyWritten);
    //    //        writer.WriteEndElement();
    //    //    }
    //    //    else
    //    //    {
    //    //        //we need to reference a node already mentioned in the document.
    //    //        writer.WriteStartElement("BindingNode");
    //    //        writer.WriteAttributeString("refID", SomeSortOfUniqueID.ToString());
    //    //        writer.WriteEndElement();
    //    //    }
    //    //}

    //    public void WriteXml(XmlWriter writer)
    //    {
    //        foreach (IEntityComponent dispatcher in this)
    //        {
    //            writer.WriteStartElement("IEntityComponent");
    //            writer.WriteAttributeString("AssemblyQualifiedName", dispatcher.GetType().AssemblyQualifiedName);
    //            XmlSerializer xmlSerializer = new XmlSerializer(dispatcher.GetType());
    //            xmlSerializer.Serialize(writer, dispatcher);
    //            writer.WriteEndElement();
    //        }
    //    }
    //}
}
