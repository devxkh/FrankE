#region License

// Copyright (c) 2013 Chandramouleswaran Ravichandran
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using Microsoft.Practices.Unity;
using System.ComponentModel;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Util;
namespace VEF.Model
{
    internal class OutputModel : ToolModel
    {
        private string _text;

        private IOutputService m_OutputService;

        public TextBoxStreamWriter TextBoxStreamWriter
        { 
            get {
                return m_OutputService.TBStreamWriter as TextBoxStreamWriter;
            } 
            set {
                m_OutputService.TBStreamWriter = value; } 
        }

        public OutputModel(IOutputService outputService)
        {
            m_OutputService = outputService; 
        }

        public string Text
        {
            get { return _text; }
        }

        public void AddLog(IOutputService Output)
        {
            _text = Output.Message + "\n" + _text;
            RaisePropertyChanged("Text");
        }
    }
}