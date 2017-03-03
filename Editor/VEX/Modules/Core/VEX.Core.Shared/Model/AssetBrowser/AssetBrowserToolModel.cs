#region License

// Copyright (c) 2013 Konrad Huber
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using System.Linq;
using Microsoft.Practices.Unity;
using VEF.Interfaces;
using VEX.Core.Shared.Interface.Services;
using VEF.Interfaces.Services;

namespace VEX.Core.Model.AssetBrowser
{
    //public class FolderTyp: IItem
    //{
    //    string ContentID { get; set; }
    //    bool HasChildren { get; }
    //    bool IsExpanded { get; set; }
    //    bool IsSelected { get; set; }
    //    ObservableCollection<IItem> Items { get; }
    //    List<System.Windows.Controls.MenuItem> MenuOptions { get; }
    //    string Name { get; set; }
    //    IItem Parent { get; }
    //    IUnityContainer UnityContainer { get; }

    //    public DirectoryInfo DirectoryInfo { get;set; }

    //    bool Delete();
    //    bool Open();
    //    bool Save();


    //}
    /// <summary>
    /// Class TextModel which contains the text of the document
    /// </summary>
    public class AssetBrowserToolModel : ToolModel
    {
        IAssetBrowserTreeService mAssetBrowserTreeService;

      //  ObservableCollection<ContentModel> mItems;
     //   ObservableCollection<DirectoryInfo> mFolders;

      //  public CollectionOfIItem Items { get { return mAssetBrowserTreeService.Items; } }
     //   public ObservableCollection<DirectoryInfo> Items { get { return mFolders; } }
        //List<IItem> mItems;
        private CollectionOfIItem m_Items;
        public CollectionOfIItem Items { get { return m_Items; }
            set { 
                m_Items = value; 
                RaisePropertyChanged("Items"); 
            } }
        //public IItem RootItem
        //{
        //    get { return mAssetBrowserTreeService.RootItem; }
        //}

        //public IItem SeRootItem
        //{
        //    get { return mAssetBrowserTreeService.RootItem; }
        //}

     //    ObservableCollection<FileInfo> files = new ObservableCollection<FileInfo>();  // List that will hold the files and subfiles in path
     ////   static ObservableCollection<DirectoryInfo> folders = new ObservableCollection<DirectoryInfo>(); // List that hold direcotries that cannot be accessed
     //    void FullDirList(DirectoryInfo dir, string searchPattern)
     //   {
     //       // Console.WriteLine("Directory {0}", dir.FullName);
     //       // list the files
     //       try
     //       {
     //           foreach (FileInfo f in dir.GetFiles(searchPattern))
     //           {
     //               //Console.WriteLine("File {0}", f.FullName);
     //               files.Add(f);
     //           }
     //       }
     //       catch
     //       {
     //           Console.WriteLine("Directory {0}  \n could not be accessed!!!!", dir.FullName);
     //           return;  // We alredy got an error trying to access dir so dont try to access it again
     //       }

     //       // process each directory
     //       // If I have been able to see the files in the directory I should also be able 
     //       // to look at its directories so I dont think I should place this in a try catch block
     //       foreach (DirectoryInfo d in dir.GetDirectories())
     //       {
     //       //    var parentFolder = mFolders.Where(x => x.Parent == d.Parent).First();
     //       //  parentFolder.add
     //           mFolders.Add(d);
     //           FullDirList(d, searchPattern);
     //       }

     //   }

        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public AssetBrowserToolModel(IUnityContainer container)//ICommandManager commandManager, IMenuService menuService)
        {

            //var itemProvider = new ItemProvider();

            //if (Directory.Exists(@"D:\Projekte\Src Game\Data\Data_Release\Assets"))
            // mItems = itemProvider.GetItems(@"D:\Projekte\Src Game\Data\Data_Release\Assets");


           var commandManager = container.Resolve<ICommandManager>();
          var menuService =  container.Resolve<IMenuService>();
           mAssetBrowserTreeService =  container.Resolve<IAssetBrowserTreeService>();

           mAssetBrowserTreeService.ABTM = this; // new CollectionOfIItem();
        //   mFolders = new ObservableCollection<DirectoryInfo>();

           //string[] entries = Directory.GetFileSystemEntries(
           //                 @"D:\Projekte\Src Game\Data\Data_Release\Assets", "*", SearchOption.AllDirectories);

           //DirectoryInfo di = new DirectoryInfo(@"D:\Projekte\Src Game\Data\Data_Release\Assets");
           //FullDirList(di, "*");
   

           //List<String[]> root = new List<String[]>();

           //foreach (var item in entries)
           //{
           //    string directory = Path.GetDirectoryName(item);
           //    string subfolder = directory.Replace(@"D:\Projekte\Src Game\Data\Data_Release\Assets\", "");

           //    root.Add(item.Split('\\'));
               
           //    string FileName = Path.GetFileName(item);
           //    string ext = Path.GetExtension(FileName);

           //    if (subfolder != String.Empty)
           //    {
           //        var foundsubfolder = mAssetBrowserTreeService.Items.Where(x => x.Name == "subfolder");
           //       if(foundsubfolder.Any())
           //       {

           //       }
           //    }
           //    //root
           //    else
           //    {
           //     if (ext != String.Empty)
           //        mAssetBrowserTreeService.Items.Add(new FileCategoryModel() { Name = FileName });
           //    else
           //        mAssetBrowserTreeService.Items.Add(new FileCategoryModel() { Name = FileName });
           //    }

              
           //}

       //    ObservableCollection<IItem> TheObservableCollection = new ObservableCollection<IItem>(TheArray);


            //tray.ContextMenu.ItemsSource = _children;

      //      mItems = new ObservableCollection<ContentModel>();


        //    CategoryModel cdata = new CategoryModel(commandManager, menuService) { Name = "Data" };
         //   mAssetBrowserTreeService.Items.Add(cdata);
            //------------- Scenes ----------------------
            //VMCategory cScenes = new VMCategory(,commandManager, menuService) { Name = "Scenes" };

            //p1.Items.Add(cScenes);

            //CVMScene sv = new CVMScene() { Name = "Scene 1" };
            //sv.Items.Add(new CVMCategory() { Name = "Cameras" });
            //sv.Items.Add(new CVMCategory() { Name = "Models" });
            //sv.Items.Add(new CVMCategory() { Name = "Sound" });
            //cScenes.Items.Add(sv);

        }

        //internal void SetLocation(object location)
        //{
        //    this.Location = location;
        //    RaisePropertyChanged("Location");
        //}

        //internal void SetDirty(bool value)
        //{
        //    this.IsDirty = value;
        //}

        public string HTMLResult { get; set; }

        public void SetHtml(string transform)
        {
            this.HTMLResult = transform;
            RaisePropertyChanged("HTMLResult");
        }
    }
}