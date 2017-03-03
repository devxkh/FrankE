using PCL.XEditor;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace VEX.Core.Shared.Service.FileWatcher
{
    public interface IFileConverter
    {
        void Convert(string sourceFilename, string destinationFolder, string destinationFileName);
    }

    public class FBXFileConverter : IFileConverter
    {

        public void Convert(string sourceFilename, string destinationFolder, string destinationFileName)
        {
            //  string fbxfilename = @"F:\Projekte\Game\3d Models\SFV\Ryu-Final\Ryu\ryu.FBX";
            string outmeshfilename = Path.Combine(destinationFolder, destinationFileName); //"test.MESH";
            string animname = "";
            string logfilename = "log.txt";
            string frame0name = "BaseFBXFrame0Anim";
            bool copyUniqueTextures = false;
            int bindframe = 0;

            DLL_FBXToOgre tmp = new DLL_FBXToOgre();
            bool result = tmp.Test_ExportOgreFromFBX(sourceFilename, outmeshfilename, logfilename, animname,
                                                         frame0name, copyUniqueTextures, bindframe);
        }
    }
}
