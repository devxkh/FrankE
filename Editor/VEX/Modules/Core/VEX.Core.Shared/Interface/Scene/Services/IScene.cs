

using VEF.Utils;

namespace VEX.Interface.Scene.Services
{
    public class Vector3 : ViewModelBase
    {
        private float m_X;
        private float m_Y;
        private float m_Z;


        public float X { get { return m_X; } set {
                m_X = value;
                RaisePropertyChanged("X"); } }
        public float Y { get { return m_Y; } set { m_Y = value; RaisePropertyChanged("Y"); } }
        public float Z { get { return m_Z; } set { m_Z = value; RaisePropertyChanged("Z"); } }

        public override string ToString()
        {
            return string.Format("{0}, {1}, {2}", X, Y, Z);
        }
    }

    public class Quaternion : ViewModelBase
    {
        private float m_W;
        private float m_X;
        private float m_Y;
        private float m_Z;

        public float W { get { return m_W; } set { m_W = value; RaisePropertyChanged("W"); } }
        public float X { get { return m_X; } set { m_X = value; RaisePropertyChanged("X"); } }
        public float Y { get { return m_Y; } set { m_Y = value; RaisePropertyChanged("Y"); } }
        public float Z { get { return m_Z; } set { m_Z = value; RaisePropertyChanged("Z"); } }

        public override string ToString()
        {
            return string.Format("{0}, {1}, {2}, {3}", W, X, Y, Z);
        }
    }

    //public interface IScene : IItem
    //{
    //    //CollectionOfISceneItem SceneItems { get; }

    //    //DAL.MDB.Scene DB_SceneData { get; }

    //    //bool AddItem(ISceneItem item);

    //    ISceneItem SelectedItem { get; set; }
    //}
}
