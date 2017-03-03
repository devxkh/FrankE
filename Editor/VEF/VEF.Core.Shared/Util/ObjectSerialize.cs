using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace VEF.VEF_Helpers
{
    public static class ObjectSerialize
    {
        public static void Serialize<T>(T dataToSerialize, string filePath, List<Type> knownTypes = null)
        {
                // Determine whether the directory exists.
                if (!Directory.Exists(Path.GetDirectoryName(filePath)))
                    Directory.CreateDirectory(Path.GetDirectoryName(filePath));

                //Serialize
                using (Stream stream = File.Open(filePath, FileMode.Create, FileAccess.ReadWrite))
                {
                    var serializer = new DataContractSerializer(typeof(T), knownTypes);
                    XmlTextWriter writer = new XmlTextWriter(stream, Encoding.UTF8);
                    serializer.WriteObject(writer, dataToSerialize);
                    writer.Close();
                }
        }

        public static T Deserialize<T>(string filePath)
        {
            T serializedData = default(T);
            
                using (Stream stream = File.Open(filePath, FileMode.Open, FileAccess.Read))
                {
                    var serializer = new DataContractSerializer(typeof(T));
                    serializedData =(T)serializer.ReadObject(stream);
                }

            return serializedData;
        }

        ///// <summary>
        ///// Serializes the data in the object to the designated file path
        ///// </summary>
        ///// <typeparam name="T">Type of Object to serialize</typeparam>
        ///// <param name="dataToSerialize">Object to serialize</param>
        ///// <param name="filePath">FilePath for the XML file</param>
        //public static void Serialize<T>(T dataToSerialize, string filePath)
        //{
        //    try
        //    {
        //        // Determine whether the directory exists.
        //        if (!Directory.Exists(Path.GetDirectoryName(filePath)))
        //            Directory.CreateDirectory(Path.GetDirectoryName(filePath));


        //        using (Stream stream = File.Open(filePath, FileMode.Create, FileAccess.ReadWrite))
        //        {
        //            XmlSerializer serializer = new XmlSerializer(typeof(T));
        //            XmlTextWriter writer = new XmlTextWriter(stream, Encoding.Default);
        //            writer.Formatting = Formatting.Indented;
        //            serializer.Serialize(writer, dataToSerialize);
        //            writer.Close();
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine("error : XMLSerializer.Serialize" + ex.Message);
        //    }
        //}


        ///// <summary>
        ///// Deserializes the data in the XML file into an object
        ///// </summary>
        ///// <typeparam name="T">Type of object to deserialize</typeparam>
        ///// <param name="filePath">FilePath to XML file</param>
        ///// <returns>Object containing deserialized data</returns>
        //public static T Deserialize<T>(string filePath)
        //{
        //    T serializedData = default(T);

        //    try
        //    {
        //        XmlSerializer serializer = new XmlSerializer(typeof(T));

        //        using (Stream stream = File.Open(filePath, FileMode.Open, FileAccess.Read))
        //        {
        //            serializedData = (T)serializer.Deserialize(stream);
        //        }

        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine("error : XMLSerializer.Serialize" + ex.Message);
        //    }


        //    return serializedData;
        //}

        //public static void SerializeObjectToXML<T>(T item, string FilePath, Type[] extraTypes)
        //{
        //    //XmlWriterSettings xmlWriterSettings = new XmlWriterSettings
        //    //{
        //    //    ConformanceLevel = ConformanceLevel.Document,
        //    //    Indent = true,
        //    //    OmitXmlDeclaration = true,
        //    //    Encoding = Encoding.UTF8
        //    //};

        //    //using (StreamWriter wr = new StreamWriter(FilePath))
        //    //{
        //    //    using (XmlWriter xmlWriter = XmlWriter.Create(wr, xmlWriterSettings))
        //    //    {
        //    //        var x = new System.Xml.Serialization.XmlSerializer(typeof(T));
        //    //        x.Serialize(wr, item);
        //    //    }
        //    //}

        //    //using (MemoryStream memoryStream = new MemoryStream())
        //    //using (XmlWriter xmlWriter = XmlWriter.Create(memoryStream, xmlWriterSettings))
        //    //{
        //    //    var x = new System.Xml.Serialization.XmlSerializer(typeof(T));
        //    //    x.Serialize(xmlWriter, item);

        //    //    // we just output back to the console for this demo.
        //    //    memoryStream.Position = 0; // rewind the stream before reading back.
        //    //    using (StreamReader sr = new StreamReader(memoryStream))
        //    //    {
        //    //        Console.WriteLine(sr.ReadToEnd());
        //    //    } // note memory stream disposed by StreamReaders Dispose()
        //    //}


        //XmlSerializer xs = new XmlSerializer(typeof(T), extraTypes);
        //    using (StreamWriter wr = new StreamWriter(FilePath))
        //    {
        //        xs.Serialize(wr, item);
        //    }
        //}

        //public static T DeSerializeObjectFromXML<T>(T item, string FilePath)
        //{
        //    //XmlSerializer xs = new XmlSerializer(typeof(T));
        //    //using (StreamWriter wr = new StreamWriter(FilePath))
        //    //{
        //    //    xs.Serialize(wr, item);
        //    //}

        //    //deserialize
        //    XmlSerializer xmlSerializer = new XmlSerializer(typeof(T));
        //    // A FileStream is needed to read the XML document.
        //    using (FileStream fs = new FileStream(FilePath, FileMode.Open))
        //    {
        //        XmlReader reader = XmlReader.Create(fs);

        //        // Use the Deserialize method to restore the object's state.
        //        return (T)xmlSerializer.Deserialize(reader);
        //        //  fs.Close();
        //    }
        //}
    }
}
