using System;
using System.Collections.Generic;
using System.Composition;
using System.Linq;
using System.Text;
using VEF.Interfaces;

namespace VEX.SocketTool
{
    [Export(typeof(IModule))]
    public class Module : IModule
    {
        //public static ModuleInformation Information
        //{
        //    get
        //    {
        //        ModuleInformation information = new ModuleInformation();
        //        information.Name = System.Reflection.Assembly.GetExecutingAssembly().GetName().Name; //"VEF.TestModule";
        //        information.Dependencies.Add(new ModuleInformation() { Name = "PCF.Core" });
        //        return information;
        //    }
        //}

        //     [ImportingConstructor]
        public Module()
        {

        }

        public void PreInitialize()
        {

        }

        public void Initialize()
        {

        }

        public void PostInitialize()
        {

        }

    }
  
}
