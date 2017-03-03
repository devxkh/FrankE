
using System;
using System.Collections.Generic;
using System.Composition.Hosting;
using System.Composition;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Reflection;
using System.IO;
using System.Xml.Serialization;
using VEF.Interfaces;
using VEX.WPF;
using Microsoft.Practices.Unity;
using VEF.Interfaces.Services;
using VEF.Interfaces.Settings;
using VEF.Model;
using VEF.View.Shell;
using VEF.Model.Services;
using VEF.Model.Settings;
using VEF.Interfaces.Themes;
using VEF;

//using System.ComponentModel.Composition;
//using System.ComponentModel.Composition.Hosting;

namespace VEX.WPF
{
    //http://blogs.msdn.com/b/bclteam/archive/2012/03/02/introducing-mef-lightweight-composition-and-an-updated-composition-provider-for-asp-net-mvc-nick.aspx

    public class InterfaceBuilder
    {
        [ImportMany("IModule")]
        public IEnumerable<IModule> Attachers { get; set; }
    }

    /// <summary>
    /// Interaktionslogik für "App.xaml"
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            //ModuleConfiguration TestObj = new ModuleConfiguration();
            //TestObj.Modules = new List<ModuleInformation>();
            //TestObj.Modules.Add(new ModuleInformation() { Dependecies = new List<ModuleInformation>() { new  ModuleInformation() { Name = "VEF", Dependecies = null } }, Name = "VEF.TestModule" });
            //TestObj.Folders = new List<string>();
            //TestObj.Folders.Add(".");
            //XmlSerializer ser = new XmlSerializer(typeof(ModuleConfiguration));
            //// Create a new file stream to write the serialized object to a file
            //TextWriter WriteFileStream = new StreamWriter(@"./modules.xml");
            //ser.Serialize(WriteFileStream, TestObj);

            //// Cleanup
            //WriteFileStream.Close();

            //List<String> folders = new List<string>();
            //folders.Add("./");

            //List<ModuleInformation> modules = new List<ModuleInformation>();
            //modules.Add(VEF.TestModule.Module.Information);

            VEFModule.UnityContainer.RegisterType<AbstractWorkspace, VEXWorkspace>(new ContainerControlledLifetimeManager());



            //WPF specific 
            ModuleLoaderWPF moduleLoader = new ModuleLoaderWPF();
            moduleLoader.LoadModules("../modules.xml"); //folders, modules);


            //     List<string> pluginFiles = Directory.GetFiles(@"D:\Projekte\coop\VEF\build\Debug\").Where(item => item.EndsWith(".dll")).ToList(); ;//, " *.dll");


            //     var ipi = (
            //          // From each file in the files.
            //          from file in pluginFiles
            //             // Load the assembly.
            //         let asm = Assembly.LoadFile(file)
            //         // For every type in the assembly that is visible outside of
            //         // the assembly.
            //     //    from type in asm.GetExportedTypes()
            //             // Where the type implements the interface.
            //       //  where type.GetCustomAttribute(typeof(IModule)) != null //.IsAssignableFrom(type)
            //         // Create the instance.
            //         select asm); //(IModule)Activator.CreateInstance(type)
            //                      // Materialize to an array.
            //                      // ).ToArray();
            ////     ipi.Where(x => x.ExportedTypes().)

            //    var list = ipi.ToList();

            //HACK: change to MEF catalog if there's a portable version available!!!!
            //List<String> moduleFiles = new List<string>();
            //moduleFiles.Add(@"D:\Projekte\coop\VEF\build\Debug\VEF.TestModule.dll");

            //List<Assembly> list = new List<Assembly>();

            //foreach (string modulefile in moduleFiles)
            //{
            //    if (File.Exists(modulefile))
            //    {
            //        if (!list.Where(x => x.FullName == Path.GetFileName(modulefile)).Any())
            //        {
            //            AssemblyName assemblyName = AssemblyName.GetAssemblyName(modulefile);
            //            Assembly assembly = Assembly.Load(assemblyName);
            //            //     var exportedTypes = assembly.ExportedTypes;//.Where(x => x.ReflectedType is IModule);//<IModule>();
            //            //     var exportedatts = CustomAttributeExtensions.GetCustomAttributes(assembly);

            //            list.Add(assembly);
            //        }
            //    }
            //}


            //var configuration = new ContainerConfiguration()
            //            .WithAssemblies(list);// typeof(IModule).Assembly);


            //using (var containerTest = configuration.CreateContainer())
            //{
            //    //  AssemblyName assemblyName = AssemblyName.GetAssemblyName("");
            //    //  Assembly assembly =  Assembly.Load(assemblyName); 

            //    var greeter = containerTest.GetExport<IModule>();
            //    string bla = greeter.Information.Name;


            //    InterfaceBuilder builder = new InterfaceBuilder();
            //    containerTest.SatisfyImports(builder);
            //}

            //CompositionHost container = new ContainerConfiguration()
            //  .WithAssembly(typeof(IModule).Assembly)
            //  .CreateContainer();



            //     var importer = new Portable.Importer();
            //     var importedName = importer.Name;

            //DirectoryCatalog  doesnt work with lightweight MEF 2 !!!!!

            //DirectoryCatalog catalog = new DirectoryCatalog(".");

            //InterfaceBuilder builder = new InterfaceBuilder();
            //CompositionContainer container = new CompositionContainer(catalog);
            //container.ComposeParts(builder);


            //foreach (IModule attacher in builder.Attachers)
            //{
            //    attacher.StartEngine("dd");
            //  //  this.pnlLoadControls.Controls.Add(attacher.GetInterfaceObject());
            ////    attacher.Container = this.pnlContainer;
            //}

            //   AppBootstrapper test = new AppBootstrapper();

            //    AppBootstrapper tmp = new AppBootstrapper();






            Application.Current.MainWindow.DataContext = VEFModule.UnityContainer.Resolve(typeof(VEXWorkspace));
        }

        void App_Loaded(object sender, RoutedEventArgs e)
        {

        }

    }
}
