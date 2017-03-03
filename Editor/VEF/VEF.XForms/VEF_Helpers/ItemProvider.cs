using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;
using VEF.Model.Services;

namespace VEF.VEF_Helpers
{
    [DataContract(IsReference = true)]
    public class Item : PItem
    {


    }

    [DataContract(IsReference = true)]
    public class FileItem : Item
    {

    }

    [DataContract(IsReference = true)]
    public class DirectoryItem : Item
    {
        [DataMember]
        public CollectionOfIItem Items { get; set; }

        public DirectoryItem()
        {
            Items = new CollectionOfIItem();
        }
    }
}
