using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using VEX.Core.Model;
using VEX.Core.Shared.Model.Project;

namespace VEX.Core.Shared.Service.FileWatcher
{
    public class FileItemWatcher : FileSystemWatcher
    {
        public SourceFileItem SourceFileItem { get; set; }
    }


}
