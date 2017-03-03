using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace VEF.Util
{
    public class TextBoxStreamWriter : TextWriter
    {
        TextBox _output = null;

        public void setTB(TextBox tb)
        {
            _output = tb;
        }

        public TextBoxStreamWriter()
        {
        }

        public override void WriteLine(String value)
        {
            base.WriteLine(value);

            if (_output == null)
                return;

            _output.Dispatcher.BeginInvoke(new Action(() =>
            {
                string str = value.ToString();
                _output.AppendText(str + (!str.EndsWith(Environment.NewLine) ? Environment.NewLine : ""));
                _output.ScrollToEnd();
            })
            ); // When character data is written, append it to the text box. 
        }


        //public override void Write(char value)
        //{
        //    base.Write(value);
        //    _output.Dispatcher.BeginInvoke(new Action(() =>
        //    {
        //        _output.AppendText(value.ToString());
        //        _output.ScrollToEnd();
        //    })
        //    ); // When character data is written, append it to the text box. 
        //}

        public override Encoding Encoding
        {
            get { return System.Text.Encoding.UTF8; }
        }
    }
}
