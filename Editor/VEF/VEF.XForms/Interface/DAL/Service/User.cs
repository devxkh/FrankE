using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Module.DB.Service
{
    public enum LogStatus
    {
        Unknown,
        LoggedIn,
        LoggedOut,
        UserNotFound,
        WrongPassword,
    }

    public class User
    {
        public Int32 UserGruppe { get; set; }
        public bool LoggedIn { get; set; }
        public long UserID { get; set; }
        public string Username { get; set; }
        public LogStatus Status { get; set; }
        public object Data { get; set; }
    }
}
