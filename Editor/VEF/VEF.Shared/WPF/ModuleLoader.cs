using System;
using System.Collections.Generic;
using System.Composition;
using System.Composition.Hosting;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using VEF.Interface;

namespace VEF.WPF
{
    #if NETFX_CORE

#else

    public class ModuleLoader : VEF.Interface.ModuleLoader
    {
        List<Assembly> list = new List<Assembly>();
        
        public void LoadModules(string configfilepath)//List<string> folders, List<ModuleInformation> modules)
        {
            //HACK: change to MEF catalog if there's a portable version available!!!!
          //  List<String> moduleFiles = new List<string>();
          //  moduleFiles.Add(@"D:\Projekte\coop\VEF\build\Debug\VEF.TestModule.dll");


            ModuleConfiguration moduleConfiguration = LoadModuleConfiguration(File.ReadAllText(configfilepath));


         
            ///----------------- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ----------------------
            //currently its not possible to load lightweight MEF Composition DLL's with Full MEF Compisition library
            //-> Dll will not be found


            //all folders
            foreach (var folder in moduleConfiguration.Folders)
            {
                //all modules
                foreach (var module in moduleConfiguration.Modules)
                {

                     foreach (var dependency in module.Dependencies)
                     {
                         AddToList(folder, dependency);
                     }

                    AddToList(folder, module);
                }
            }

            LoadAssemblies(list);
        }

        void AddToList(string folder, ModuleInformation module)
        {
            String fileName = Path.GetFullPath(folder) + "/" + module.Name + ".dll";
            if (File.Exists(fileName))
            {
                //add to list if not already added
                if (!list.Where(x => x.ManifestModule.Name.Replace(".dll", "") == module.Name).Any())
                {
                    AssemblyName assemblyName = AssemblyName.GetAssemblyName(fileName);
                    Assembly assembly = Assembly.Load(assemblyName);
                    //     var exportedTypes = assembly.ExportedTypes;//.Where(x => x.ReflectedType is IModule);//<IModule>();
                    //     var exportedatts = CustomAttributeExtensions.GetCustomAttributes(assembly);

                    list.Add(assembly);
                }
            }
            else
            {
                Console.WriteLine("Error: VEF.WPF.ModuleLoader.LoadModules - File not found:" + fileName);
            }
        }
    }

#endif

}
