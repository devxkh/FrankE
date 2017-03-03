using ICSharpCode.AvalonEdit.Document;
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using VEF.Interfaces.Services;
using VEF.Model.Services;

namespace VEF.Core.Model
{
    /// <summary>
    /// Class TextModel which contains the text of the document
    /// </summary>
    public class XMLModel :  PItem
    {
        protected readonly ICommandManager _commandManager;
        protected readonly IMenuService _menuService;
        protected string OldText;

        [XmlIgnore]
        public TextDocument Document { get; protected set; }

        [XmlIgnore]
        public override bool IsDirty { get; set; }
    

        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public XMLModel(ICommandManager commandManager, IMenuService menuService)
        {
            Document = new TextDocument();

            //------------- Scenes ----------------------
            //VMCategory cScenes = new VMCategory(,commandManager, menuService) { Name = "Scenes" };

            //p1.Items.Add(cScenes);

            //CVMScene sv = new CVMScene() { Name = "Scene 1" };
            //sv.Items.Add(new CVMCategory() { Name = "Cameras" });
            //sv.Items.Add(new CVMCategory() { Name = "Models" });
            //sv.Items.Add(new CVMCategory() { Name = "Sound" });
            //cScenes.Items.Add(sv);

        }

        internal void SetLocation(object location)
        {
            this.Location = location;
            RaisePropertyChanged("Location");
        }

        internal void SetDirty(bool value)
        {
            this.IsDirty = value;
        }
            
    }
}
