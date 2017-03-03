using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.PFExplorer;
using VEF.Interfaces.Services;

namespace VEF.Utils
{
    public class PFUtilities
    {
        /// <summary>
        /// Get parent root project folder
        /// </summary>
        /// <param name="parent"></param>
        /// <returns></returns>
        public static object GetRekursivParentPF(object parent)
        {
            var item = parent as IItem;

            if (parent is IProjectFile)
            {
                return parent; //found
            }
            else if (item == null || item.Parent == null)
            {
                return null;
            }
            else
            {
                return GetRekursivParentPF(item.Parent);
            }
        }

        /// <summary>
        /// Get current folder for item
        /// </summary>
        /// <param name="parent"></param>
        /// <returns></returns>
        public static object GetRekursivPFolder(object item, ref string folderName)
        {
            var isItem = item as IItem;

            if (isItem is IProjectFile)
            {
                folderName = isItem.Name + "\\" + folderName;
                return isItem; //found
            }
            else if (isItem == null || isItem.Parent == null)
            {
                return null;
            }
            else
            {
                folderName = isItem.Name + "\\" + folderName;
                return GetRekursivPFolder(isItem.Parent, ref folderName);
            }
        }
    }
}
