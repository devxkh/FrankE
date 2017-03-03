#region License

// Copyright (c) 2013 Chandramouleswaran Ravichandran
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using Prism.Events;
using System;
using System.Configuration;
using System.Windows;
using VEF.Interfaces.Settings;
using VEF.Model.Events;
using System.Collections.Generic;
using VEF.Interfaces.Controls;
using Prism.Commands;
using VEF.Interfaces.Services;
using Microsoft.Practices.Unity;
using VEF.Interfaces;
using System.Xml.Serialization;
using VEF.Model.Settings;
using VEF.Model.Services;
using System.Windows.Input;

namespace VEF.Model.Settings
{
    internal class RecentViewSettings : AbstractSettings, IRecentViewSettings
    {
        private AbstractMenuItem recentMenu;
        private List<string> menuGuids;
        private DelegateCommand<string> recentOpen;
        private IOpenDocumentService fileService;
        private IUnityContainer _container;

        public RecentViewSettings(IUnityContainer container)
        {
            recentMenu = new MenuItemViewModel("Recentl_y opened..", 100);
            menuGuids = new List<string>();
            recentOpen = new DelegateCommand<string>(ExecuteMethod);
            this._container = container;
        }

        [UserScopedSetting()]
        public List<RecentViewItem> ActualRecentItems
        {
            get
            {
                if ((List<RecentViewItem>) this["ActualRecentItems"] == null)
                    this["ActualRecentItems"] = new List<RecentViewItem>((int) TotalItems);
                return (List<RecentViewItem>) this["ActualRecentItems"];
            }
            set { this["ActualRecentItems"] = value; }
        }

        [UserScopedSetting()]
        [DefaultSettingValue("10")]
        public uint TotalItems
        {
            get { return (uint) this["TotalItems"]; }
            set
            {
                this["TotalItems"] = value;
                ActualRecentItems.Capacity = (int) value;
                menuGuids.Capacity = (int) value;
            }
        }

        public void Update(ContentViewModel viewModel)
        {
            if (viewModel.Model == null)
                return;

            RecentViewItem item = new RecentViewItem();
            item.ContentID = viewModel.Model.ContentID;

            if (viewModel.Model.Location != null)
             item.DisplayValue = viewModel.Model.Location.ToString();

            if (ActualRecentItems.Contains(item))
            {
                ActualRecentItems.Remove(item);
            }
            ActualRecentItems.Add(item);
            this.Save();
            RecentMenu.Refresh();
        }

        private void ExecuteMethod(string s)
        {
            if (fileService == null)
            {
                fileService = _container.Resolve<IOpenDocumentService>();
            }
            fileService.OpenFromID(s, true);
        }

        [XmlIgnore]
        public AbstractMenuItem RecentMenu
        {
            get
            {
                if (RecentItems == null)
                    return recentMenu;

                int i = RecentItems.Count;
                foreach (string guid in menuGuids)
                {
                    recentMenu.Remove(guid);
                    i--;
                }

                menuGuids.Clear();

                for (i = RecentItems.Count; i > 0; i--)
                {
                    int priority = RecentItems.Count - i + 1;
                    string number = "_" + priority.ToString() + " " + RecentItems[i - 1].DisplayValue;
                    menuGuids.Add(recentMenu.Add(new MenuItemViewModel(number, priority, null, recentOpen as ICommand, null)
                                                     {CommandParameter = RecentItems[i - 1].ContentID}));
                }
                return recentMenu;
            }
        }

        [XmlIgnore]
        //IReadOnlyList -> .Net 4.5
        public IList<IRecentViewItem> RecentItems
        {
            get { return this.ActualRecentItems as IList<IRecentViewItem>; } //.AsReadOnly(); }
        }
        
    }
}