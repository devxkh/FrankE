using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PCL.XEditor
{
    public class DLL_FBXToOgre : DLL_Loader
    {
        #region Imports

        [DllImport(@"FBXTOOGRE.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern bool AddFBXAnimationToExisting([MarshalAs(UnmanagedType.LPStr)] string fbxfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string skeletonfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string meshfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string logfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string animname,
                                                        int start,
                                                        int stop,
                                                        float rate);

        [DllImport(@"FBXTOOGRE.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern bool ExportOgreFromFBX([MarshalAs(UnmanagedType.LPStr)] string fbxfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string outmeshfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string logfilename,
                                                        [MarshalAs(UnmanagedType.LPStr)] string animname,
                                                        [MarshalAs(UnmanagedType.LPStr)] string frame0name,
                                                        bool copyUniqueTextures,
                                                        int bindframe);


        public bool Test_AddFBXAnimationToExisting(string fbxfilename, string skeletonfilename, string meshfilename, string logfilename,
                                                        string animname, int start, int stop, float rate)
        {
            try
            {
                if (DLLPtr == IntPtr.Zero)
                    fLoadDLL(@"FBXTOOGRE.dll", ref DLLPtr);

                return AddFBXAnimationToExisting(fbxfilename, skeletonfilename, meshfilename, logfilename,
                                                         animname, start, stop, rate);
            }
            catch (Exception ex)
            {

            }
            return false;
        }


        private IntPtr DLLPtr = IntPtr.Zero;

        public bool Test_ExportOgreFromFBX(string fbxfilename, string outmeshfilename, string logfilename, string animname,
                                                       string frame0name, bool copyUniqueTextures, int bindframe)
        {
            try
            {
                if(DLLPtr == IntPtr.Zero)
                    fLoadDLL(@"FBXTOOGRE.dll", ref DLLPtr);


                return ExportOgreFromFBX(fbxfilename, outmeshfilename, logfilename, animname,
                                                                      frame0name, copyUniqueTextures, bindframe);

            }
            catch (Exception ex)
            {
     
            }
            return false;
        }
        #endregion
    }
}
