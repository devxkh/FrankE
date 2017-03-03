using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;

namespace VEX.Core.View.Editor.Helper
{
    public partial class ElementViewTemplateSelector : DataTemplateSelector
    {
        private DataTemplate m_ImageTemplate;

        public DataTemplate ImageTemplate
        {
            get { return m_ImageTemplate; }
            set { m_ImageTemplate = value; }
        }

        private DataTemplate m_ColorTemplate;

        public DataTemplate ColorTemplate
        {
            get { return m_ColorTemplate; }
            set { m_ColorTemplate = value; }
        }


        private List<DataTemplate> m_DataTemplates = new List<DataTemplate>();

        public void AddDataTemplate(DataTemplate dataTemplate)
        {
            m_DataTemplates.Add(dataTemplate);
        }

        //private DataTemplate parameterListTemplate;

        //public DataTemplate ParameterListTemplate
        //{
        //    get { return parameterListTemplate; }
        //    set { parameterListTemplate = value; }
        //}

        //private DataTemplate ipTemplate;

        //public DataTemplate IPTemplate
        //{
        //    get { return ipTemplate; }
        //    set { ipTemplate = value; }
        //}

        private DataTemplate defaultTemplate;

        public DataTemplate DefaultTemplate
        {
            get { return defaultTemplate; }
            set { defaultTemplate = value; }
        }

        public DataTemplate AnimationNodeTemplate { get; set; }
        public DataTemplate TransistionSelectNodeTemplate { get; set; }
        public DataTemplate OutputNodeTemplate { get; set; }
        public DataTemplate ParameterNodeTemplate { get; set; }


        //private DataTemplate textBoxTemplate;

        //public DataTemplate TextBoxTemplate
        //{
        //    get { return textBoxTemplate; }
        //    set { textBoxTemplate = value; }
        //}


        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            //Node types
            if (item is DLL.NodeEditor.Nodes.ColorInput)
                return m_ColorTemplate;
            else if (item is DLL.NodeEditor.Nodes.Multiply)
                return m_ColorTemplate;

            else if (item is AnimationNodeViewModel)
                return AnimationNodeTemplate;
            else if (item is TransitionSelectNodeViewModel)
                return TransistionSelectNodeTemplate;
            else if (item is OutputNodeViewModel)
                return OutputNodeTemplate;
            else if (item is ParameterNodeViewModel)
                return ParameterNodeTemplate;
            //else if (item is MixNodeViewModel)
            //    return MixNodeTemplate;
            //    //ParameterFunktion place = (ParameterFunktion)item;

            //    //if (place != null)
            //    //{
            //    //    switch (place.FunktionID)
            //    //    {
            //    //        // case FunktionID.Abrechnung: return parameterListTemplate;
            //    //        case FunktionID.Abrechnungsdaten_Überschreiben: return parameterListTemplate;
            //    //        case FunktionID.DatumSetzen: return datumTemplate;
            //    //        //   case FunktionID.GeräteInit: return parameterListTemplate;
            //    //        // case FunktionID.ProgVersionAnzeige: return parameterListTemplate;
            //    //        // case FunktionID.Reboot: return datumTemplate;
            //    //        case FunktionID.XPortSetup: return parameterListTemplate;
            //    //        default: return defaultTemplate;
            //    //    }
            //    //}
            //   return m_DataTemplates[0];
            return defaultTemplate;
        }
    }
}
