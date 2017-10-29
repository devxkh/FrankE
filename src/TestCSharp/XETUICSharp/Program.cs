using System;
using System.ComponentModel;

namespace XETUICSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {

                XGame.Core.XGame game = new XGame.Core.XGame()
                {
                    ResourceConfigFile = "E:/Projekte/coop/XEngine/data/Test/XETController/resources.cfg",
                    Title = "C# Test"
                };
                game.Run();
            }
            catch (Win32Exception e)
            {
                Console.WriteLine("error:" + e.Message + ",nc:" + e.NativeErrorCode);
            }
            catch (Exception e)
            {
                Console.WriteLine("error:" + e.Message);
            }
        }
    }
}
