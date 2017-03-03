using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Utils;

namespace VEF.Interfaces.Base
{
    /// <summary>
    /// Class AbstractPrioritizedTree
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public abstract class AbstractPrioritizedTree<T> : ViewModelBase, IPrioritizedTree<T>
        where T : AbstractPrioritizedTree<T>
    {
        /// <summary>
        /// The children of this tree node
        /// </summary>
        protected ObservableCollection<T> _children;

        /// <summary>
        /// Initializes a new instance of the <see cref="AbstractPrioritizedTree{T}"/> class.
        /// </summary>
        protected AbstractPrioritizedTree()
        {
            _children = new ObservableCollection<T>();
        }

        #region IPrioritizedTree<T> Members

        /// <summary>
        /// Adds the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <returns><c>true</c> if successfully added, <c>false</c> otherwise</returns>
        public virtual string Add(T item)
        {
            _children.Add(item);
            item.GuidString = Guid.NewGuid().ToString();
            RaisePropertyChanged("Children");
            return item.GuidString;
        }

        /// <summary>
        /// Removes the specified key.
        /// </summary>
        /// <param name="GuidString">The unique GUID set for the menu available for the creator.</param>
        /// <returns><c>true</c> if successfully removed, <c>false</c> otherwise</returns>
        public virtual bool Remove(string GuidString)
        {
            IEnumerable<T> items = _children.Where(f => f.GuidString == GuidString);
            if (items.Any())
            {
                _children.Remove(items.ElementAt(0));
                RaisePropertyChanged("Children");
                return true;
            }
            return false;
        }

        /// <summary>
        /// Gets the node with the specified key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>`0.</returns>
        public virtual T Get(string key)
        {
            IEnumerable<T> items = _children.Where(f => f.Key == key);
            if (items.Any())
            {
                return items.ElementAt(0);
            }
            return default(T);
        }

        /// <summary>
        /// Gets the children.
        /// </summary>
        /// <value>The children.</value>
        [Display(AutoGenerateField=false)]
        public virtual ReadOnlyObservableCollection<T> Children
        {
            get
            {
                IOrderedEnumerable<T> order = from c in _children
                                              orderby c.Priority
                                              select c;
                return new ReadOnlyObservableCollection<T>(new ObservableCollection<T>(order.ToList()));
            }
        }

        /// <summary>
        /// Gets the priority.
        /// </summary>
        /// <value>The priority.</value>
        [Display(AutoGenerateField = false)]
        public virtual int Priority { get; protected set; }

        /// <summary>
        /// Gets the key.
        /// </summary>
        /// <value>The key.</value>
        [Display(AutoGenerateField = false)]
        public virtual string Key { get; protected set; }

        protected string GuidString { get; set; }

        #endregion
    }
}
