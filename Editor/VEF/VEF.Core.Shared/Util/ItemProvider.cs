using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using VEF.Interfaces.Services;
using VEF.VEF_Helpers;

namespace VEF.Core.Util
{
    public class ItemProvider
    {
        public CollectionOfIItem GetItems(string path)
        {
            var items = new CollectionOfIItem();

            var dirInfo = new DirectoryInfo(path);

            foreach (var directory in dirInfo.GetDirectories())
            {
                var item = new DirectoryItem
                {
                    Name = directory.Name,
                    ContentID = directory.FullName,
                    Items = GetItems(directory.FullName)
                };

                items.Add(item);
            }

            foreach (var file in dirInfo.GetFiles())
            {
                var item = new FileItem
                {
                    Name = file.Name,
                    ContentID = file.FullName
                };

                items.Add(item);
            }

            return items;
        }
    }

}
