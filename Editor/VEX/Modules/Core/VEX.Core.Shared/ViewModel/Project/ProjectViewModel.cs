#region License

//The MIT License (MIT)

//Copyright (c) 2014 Konrad Huber

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#endregion

using System.Windows.Controls;
using System.Windows.Input;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Services;

namespace VEX.Core.ViewModel.Project
{
    internal class VEXProjectViewModel : ContentViewModel
    {
        public VEXProjectViewModel(AbstractWorkspace workspace, ICommandManager commandManager, ILoggerService logger,
                           IMenuService menuService)
            : base(workspace, commandManager, menuService)
        {
           // ICommand mOpenCOMCommand;
           //OpenCOMCommand mOpenComCommand;
           // mOpenComCommand = new Commands.OpenCOMCommand();
           // mOpenCOMCommand = new DelegateCommand<OpenCOMCommand>(
           //                           mOpenComCommand.OnSubmit, mOpenComCommand.CanSubmit);
        }

     //   public ICommand OpenCOMCommand { get { return mOpenCOMCommand; } }


        internal void SetModel(PItem model)
        {
            base.Model = model;
        }

        internal void SetView(UserControl view)
        {
            base.View = view;
        }

        internal void SetHandler(IContentHandler handler)
        {
            base.Handler = handler;
        }
    }
}