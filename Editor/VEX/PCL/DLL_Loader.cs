using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace PCL.XEditor
{
    public class DLL_Loader
    {
        [DllImport("kernel32", SetLastError = true)]
        private static extern IntPtr LoadLibrary(string librayName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true, CallingConvention = CallingConvention.StdCall)]//, SuppressUnmanagedCodeSecurity]
        internal static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        // [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi, EntryPoint = "GetProcAddress", ExactSpelling = true, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        // private static extern IntPtr GetProcAddress(IntPtr hModule, [MarshalAs(UnmanagedType.LPStr)] string lpProcName);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool FreeLibrary(IntPtr hModule);

        [DllImport("msvcrt.dll")]
        private static extern int _controlfp(int IN_New, int IN_Mask); // this imports the call
        private const int _MCW_EM = 0x0008001f;
        private const int _EM_INVALID = 0x00000010;

        [DllImport("msvcr70.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fPreset();

        /// <summary>
        /// Bugfix für .Net 3.5 ?????
        /// </summary>
        public void fTest()
        {
            _controlfp(_MCW_EM, _EM_INVALID); // this is the call
        }

        /// <summary>
        /// Gibt die DLL frei
        /// </summary>
        /// <param name="hmod">Pointer auf Funktion</param>
        /// <returns>0 = keine Fehler, ErrorID</returns>
        public Int32 fFreeDLL(IntPtr hmod)
        {
            int error = 0;

            //    CPManager.Instance.VMLog.fAddLog(Log.DLL_LOADER, "Versuche DLL (hmod: " + hmod + ") freizugeben", LogLvl.Debug);

            FreeLibrary(hmod);

            // Get the last error and display it.
            error = Marshal.GetLastWin32Error();

            //      CPManager.Instance.VMLog.fAddLog(Log.DLL_LOADER, "fFreeDLL (hmod: " + hmod + ",error: " + error + ")", LogLvl.Debug);

            return error;
        }

        /// <summary>
        /// Lädt eine DLL
        /// </summary>
        /// <param name="pDLLPath">Pfad zur DLL</param>
        /// <returns>ErrorID, 0 = keine Fehler</returns>
      //test  [Display(Description = "Personalnummer", Name = "Personalnummer", GroupName = "Identifikation")]
        public Int32 fLoadDLL(String pDLLPath, ref IntPtr hmod)
        {
            int error = 0;

            try
            {
                hmod = LoadLibrary(pDLLPath);

                // Get the last error and display it.
                error = Marshal.GetLastWin32Error();

                //## MessageBox.Show("LoadLibrary: The last Win32 Error was: " + error);
               if (hmod == IntPtr.Zero || error > 0)
                {

                }
                        //  Console.Wr.CErrLog.fAddError("Fehler " + error + ",hmod(" + hmod + ") bei Laden der DDL Datei:" + pDLLPath, null, true);
              //  Utility.CErrLog.fAddError("Fehler " + error + ",hmod(" + hmod + ") bei Laden der DDL Datei:" + pDLLPath, null, true);

            }
            catch (Exception ex)
            {
                //       Utility.CErrLog.fAddError("Fehler (" + error + ") " + ex.Message + ",hmod(" + hmod + ") bei Laden der DDL Datei:" + pDLLPath, null, true);
            }
            //## if (hmod == IntPtr.Zero)
            //##     MessageBox.Show("Fehler bei Laden von :" + pDLLPath);

            //     FixFPU();

            //Sehr wichtig für Floating Point Fehler nach Zugriff auf Unmanaged Code
            /*    try
                {
                 //   _controlfp(_MCW_EM, _EM_INVALID); // this is the call
                }catch(Exception ex){
                      Utility.CErrLog.fAddError("Fehler bei DLL Loader:" + ex.Message, ex, false, true);
                }*/
            return error;
        }

        /// <summary>
        /// Lädt eine Funktion innerhalb einer DLL
        /// </summary>
        /// <param name="pFktName">Funktionsname</param>
        /// <param name="hmod">DLL Pointer</param>
        /// <returns>Pointer auf Funktion innerhalb der DLL</returns>
        public IntPtr fLoadDLL_Fkt(String pFktName, IntPtr hmod)
        {
            IntPtr fptr = IntPtr.Zero;

            try
            {
                // IntPtr fptr = Window1.GetProcAddress(hmod, "UsbPower");
                fptr = DLL_Loader.GetProcAddress(hmod, pFktName);


                // Get the last error and display it.
                int error = Marshal.GetLastWin32Error();

                //##         MessageBox.Show("GetProcAddress:The last Win32 Error was: " + error);

                // IntPtr fptr = Window1.GetProcAddress(hmod, "USExcelRunReport");

                //  IntPtr fptr = Window1.GetProcAddress(hmod, "USExcelDestroy");
                // IntPtr address = GetProcAddress(hmod, "PslCreate");
                //##     MessageBox.Show("LibraryPointer:" + hmod + "#FunktionPointer:" + fptr);

                //        CPManager.Instance.VMLog.fAddLog(Log.DLL_LOADER, "DLL (err: " + error + ",Ptr: " + fptr + ") Funktion:" + pFktName, LogLvl.Debug);

                if (fptr == IntPtr.Zero)
                {
                    //          Utility.CErrLog.fAddError("Fehler (err:" + error + ") beim auslesen DLL Funktion:" + pFktName, null, true);

                    //  USExcelRunReportdelegate test = (USExcelRunReportdelegate)Marshal.GetDelegateForFunctionPointer(fptr, typeof(USExcelRunReportdelegate));
                    //##    USExcelRunReportdelegate test = (USExcelRunReportdelegate)Marshal.GetDelegateForFunctionPointer(fptr, typeof(USExcelRunReportdelegate));
                    //##    MessageBox.Show("Fkt:" + test()); //PslCreate(1, 1, 'a'));// call via a function pointer
                }
            }
            catch (Exception ex)
            {
                //       Utility.CErrLog.fAddError("Fehler bei fLoadDLL_Fkt(" + pFktName + ")", ex, false);
                //##    MessageBox.Show("Fehler: " + ex.Message);
            }
            finally
            {
                //   Window1.FreeLibrary(hmod);
            }
            //   _controlfp(_MCW_EM, _EM_INVALID); // this is the call
            return fptr;
        }
    }
}
