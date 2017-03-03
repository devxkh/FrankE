using System;
using System.Collections.Generic;
using System.Composition;
using System.Composition.Hosting;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace VEF.Interface
{
    public class InterfaceBuilder
    {
        [ImportMany("IModule")]
        public IEnumerable<IModule> Attachers { get; set; }
    }

    public class ModuleLoader
    {
        //todo protable MEF catalog library needed?????

        protected ModuleConfiguration LoadModuleConfiguration(string xml)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(ModuleConfiguration));

            XmlReaderSettings settings = new XmlReaderSettings();
            // No settings need modifying here

            using (StringReader textReader = new StringReader(xml))
            {
                using (XmlReader xmlReader = XmlReader.Create(textReader, settings))
                {
                    return (ModuleConfiguration)serializer.Deserialize(xmlReader);
                }
            }
        }

        protected void LoadAssemblies(List<Assembly> assemblies)
        {
            var configuration = new ContainerConfiguration()
                     .WithAssemblies(assemblies);// typeof(IModule).Assembly);

            try
            {
                using (var containerTest = configuration.CreateContainer())
                {
                    //  AssemblyName assemblyName = AssemblyName.GetAssemblyName("");
                    //  Assembly assembly =  Assembly.Load(assemblyName); 
                    var modules = containerTest.GetExports<IModule>();//.Select(e => new Lazy<IModule>(() => e));
               //     var modules = containerTest.GetExports<IModule>();

                    foreach(var module in modules)
                    {
                            module.Initialize();
                    }

                    InterfaceBuilder builder = new InterfaceBuilder();
                    containerTest.SatisfyImports(builder);
                }

            }
            catch (ReflectionTypeLoadException loadEx)
            {

            }
            catch (Exception ex)
            {
            }


        }
    }
    //public void LoadModules()
    //{

    //    //HACK: change to MEF catalog if there's a portable version available!!!!
    //    List<String> moduleFiles = new List<string>();
    //    moduleFiles.Add(@"D:\Projekte\coop\VEF\build\Debug\VEF.TestModule.dll");


    //    List<Assembly> list = new List<Assembly>();

    //    //currently its not possible to load lightweight MEF Composition DLL's with Full MEF Compisition library
    //    //-> Dll will not be found

    //    foreach (string modulefile in moduleFiles)
    //    {
    //        if (File.Exists(modulefile))
    //        {
    //            if (!list.Where(x => x.FullName == Path.GetFileName(modulefile)).Any())
    //            {
    //                AssemblyName assemblyName = AssemblyName.GetAssemblyName(modulefile);
    //                Assembly assembly = Assembly.Load(assemblyName);
    //                //     var exportedTypes = assembly.ExportedTypes;//.Where(x => x.ReflectedType is IModule);//<IModule>();
    //                //     var exportedatts = CustomAttributeExtensions.GetCustomAttributes(assembly);

    //                list.Add(assembly);
    //            }
    //        }
    //    }


    //    var configuration = new ContainerConfiguration()
    //                .WithAssemblies(list);// typeof(IModule).Assembly);


    //    using (var containerTest = configuration.CreateContainer())
    //    {
    //        //  AssemblyName assemblyName = AssemblyName.GetAssemblyName("");
    //        //  Assembly assembly =  Assembly.Load(assemblyName); 

    //        var greeter = containerTest.GetExport<IModule>();
    //        String bla = greeter.Information.Name;


    //        InterfaceBuilder builder = new InterfaceBuilder();
    //        containerTest.SatisfyImports(builder);
    //    }

    //}



}
