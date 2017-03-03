using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using VEF.View.Types;
using VEX.Core.Shared.Service.Scene;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Shared.ViewModel.Editor.Components
{
    public class ComponentsList<T> : ObservableCollection<T>, ICustomTypeDescriptor
    {
        // Implementation of ICustomTypeDescriptor: 
        PropertyDescriptorCollection ICustomTypeDescriptor.GetProperties()
        {
            // Create a collection object to hold property descriptors
            PropertyDescriptorCollection pds = new PropertyDescriptorCollection(null);

            for (int i = 0; i < Count; i++)
            {
                ComponentX comp = this[i] as ComponentX;
                if (comp != null)
                    pds.Add(new ItemPropertyDescriptor<T>(this, i, comp.Name));
                else
                    pds.Add(new ItemPropertyDescriptor<T>(this, i, i.ToString()));
            }

            return pds;
        }

        #region Use default TypeDescriptor stuff

        AttributeCollection ICustomTypeDescriptor.GetAttributes()
        {
            return TypeDescriptor.GetAttributes(this, noCustomTypeDesc: true);
        }

        string ICustomTypeDescriptor.GetClassName()
        {
            return TypeDescriptor.GetClassName(this, noCustomTypeDesc: true);
        }

        string ICustomTypeDescriptor.GetComponentName()
        {
            return TypeDescriptor.GetComponentName(this, noCustomTypeDesc: true);
        }

        TypeConverter ICustomTypeDescriptor.GetConverter()
        {
            return TypeDescriptor.GetConverter(this, noCustomTypeDesc: true);
        }

        EventDescriptor ICustomTypeDescriptor.GetDefaultEvent()
        {
            return TypeDescriptor.GetDefaultEvent(this, noCustomTypeDesc: true);
        }

        PropertyDescriptor ICustomTypeDescriptor.GetDefaultProperty()
        {
            return TypeDescriptor.GetDefaultProperty(this, noCustomTypeDesc: true);
        }

        object ICustomTypeDescriptor.GetEditor(Type editorBaseType)
        {
            return TypeDescriptor.GetEditor(this, editorBaseType, noCustomTypeDesc: true);
        }

        EventDescriptorCollection ICustomTypeDescriptor.GetEvents()
        {
            return TypeDescriptor.GetEvents(this, noCustomTypeDesc: true);
        }

        EventDescriptorCollection ICustomTypeDescriptor.GetEvents(Attribute[] attributes)
        {
            return TypeDescriptor.GetEvents(this, attributes, noCustomTypeDesc: true);
        }

        PropertyDescriptorCollection ICustomTypeDescriptor.GetProperties(Attribute[] attributes)
        {
            return TypeDescriptor.GetProperties(this, attributes, noCustomTypeDesc: true);
        }

        object ICustomTypeDescriptor.GetPropertyOwner(PropertyDescriptor pd)
        {
            return this;
        }

        #endregion
    }

    public class ItemPropertyDescriptor<T> : PropertyDescriptor
    {
        private readonly ObservableCollection<T> _owner;
        private readonly int _index;

        public ItemPropertyDescriptor(ObservableCollection<T> owner, int index, string name)
          : base("#" + name, null)
        {
            _owner = owner;
            _index = index;
        }

        public override AttributeCollection Attributes
        {
            get
            {
                var attributes = TypeDescriptor.GetAttributes(GetValue(null), false);
                if (!attributes.OfType<ExpandableObjectAttribute>().Any())
                {
                    // copy all the attributes plus an extra one (the
                    // ExpandableObjectAttribute)
                    // this ensures that even if the type of the object itself doesn't have the
                    // ExpandableObjectAttribute, it will still be expandable. 
                    var newAttributes = new Attribute[attributes.Count + 1];
                    int i = 0;
                    foreach (Attribute attribute in attributes)
                    {
                        newAttributes[i] = attribute;
                        i++;
                    }
                   // Array.Copy(attributes, 0, newAttributes, 0, newAttributes.Length - 1);

                  //  attributes.CopyTo(newAttributes, newAttributes.Length - 1);
                    newAttributes[newAttributes.Length - 1] = new ExpandableObjectAttribute();

                    // overwrite the array
                    attributes = new AttributeCollection(newAttributes);
                }

                return attributes;
            }
        }

        public override bool CanResetValue(object component)
        {
            return false;
        }

        public override object GetValue(object component)
        {
            return Value;
        }

        private T Value
          => _owner[_index];

        public override void ResetValue(object component)
        {
            throw new NotImplementedException();
        }

        public override void SetValue(object component, object value)
        {
            _owner[_index] = (T)value;
        }

        public override bool ShouldSerializeValue(object component)
        {
            return false;
        }

        public override Type ComponentType
        {
            get
            {
                return _owner.GetType();
            }
        }
        //     => _owner.GetType();

        public override object GetEditor(Type editorBaseType)
        {
            var test = base.GetEditor(editorBaseType);

            return test;
        }

        public override bool IsReadOnly
          => false;

        public override Type PropertyType
        {
            get
            {
                return Value?.GetType();
            }
        }

        //public override Type PropertyType
        //   => Value?.GetType();
    }
}
