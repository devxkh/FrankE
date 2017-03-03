using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace VEF.Interfaces.Services
{
    public class CollectionOfIItem : ObservableCollection<IItem>, IXmlSerializable
    {
        public CollectionOfIItem() : base() { }

        public System.Xml.Schema.XmlSchema GetSchema() { return null; }

        public void ReadXml(XmlReader reader)
        {
            try
            {
                Boolean isMainEmptyElement = reader.IsEmptyElement; // (1)

                reader.ReadStartElement("Items");

                if (!isMainEmptyElement)
                {
                    while (reader.IsStartElement("IItem"))
                    {
                        Type type = Type.GetType(reader.GetAttribute("AssemblyQualifiedName"));
                        XmlSerializer serial = new XmlSerializer(type);

                        Boolean isEmptyElement = reader.IsEmptyElement; // (1)


                        reader.ReadStartElement("IItem");

                        if (!isEmptyElement)
                        {
                            var item = (IItem)serial.Deserialize(reader);
                            this.Add(item);


                            reader.ReadEndElement();
                        }
                    }

                    reader.ReadEndElement();
                }
            }
            catch (Exception ex)
            {

            }
        }

        public void WriteXml(XmlWriter writer)
        {
            foreach (IItem dispatcher in this)
            {
                writer.WriteStartElement("IItem");
                writer.WriteAttributeString("AssemblyQualifiedName", dispatcher.GetType().AssemblyQualifiedName);
                XmlSerializer xmlSerializer = new XmlSerializer(dispatcher.GetType());
                xmlSerializer.Serialize(writer, dispatcher);
                writer.WriteEndElement();
            }
        }
    }
}