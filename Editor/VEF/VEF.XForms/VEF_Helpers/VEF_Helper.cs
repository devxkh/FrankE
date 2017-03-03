using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace VEF.VEF_Helpers
{
    public interface IObjectEvent
    {

    }

    public struct ContentID_Data
    {
        public string Identifier {get;set;}
        public string Value {get;set;}
        public Int32 IntValue { get; set; }
    }

    public static class VEF_Helper
    {
        public static ContentID_Data StringToContentIDData(String contentIDData)
        {
            ContentID_Data data = new ContentID_Data();

            string[] split = Regex.Split(contentIDData, ":##:");
            if (split.Count() == 2)
            {
                data.Identifier = split[0];
                data.Value= split[1];
 
                Int32 tmp;
                Int32.TryParse(split[1], out tmp);
                data.IntValue = tmp;
            }

            return data;
        }

        public static string ContentIDDataToString(ContentID_Data contentIDData)
        {

            return contentIDData.Identifier + ":##:" + contentIDData.Value;
        }
    }
}
