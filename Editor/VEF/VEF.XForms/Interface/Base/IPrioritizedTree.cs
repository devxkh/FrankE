using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interfaces.Base
{
    /// <summary>
    /// Interface IPrioritizedTree
    /// </summary>
    /// <typeparam name="T"></typeparam>
    internal interface IPrioritizedTree<T>
    {
        /// <summary>
        /// Gets the children.
        /// </summary>
        /// <value>The children.</value>
        ReadOnlyObservableCollection<T> Children { get; }

        /// <summary>
        /// Gets the priority of this instance.
        /// </summary>
        /// <value>The priority.</value>
        int Priority { get; }

        /// <summary>
        /// Adds the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <returns>A GUID string for the menu</returns>
        string Add(T item);

        /// <summary>
        /// Removes the item with the GUID.
        /// </summary>
        /// <param name="GuidString">The unique GUID set for the menu available for the creator.</param>
        /// <returns><c>true</c> if successfully removed, <c>false</c> otherwise</returns>
        bool Remove(string GuidString);

        /// <summary>
        /// Gets the specified node in the tree with this key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>`0.</returns>
        T Get(string key);
    }
}
