#pragma once

#include <vector>
#include <list>

namespace Ogre
{
	class ObjectMemoryManager;
	class Vector3;
	class ColourValue;
	class ManualObject;
}

namespace XE
{
	typedef std::pair<Ogre::Vector3, Ogre::ColourValue> VertexPair;

	class GraphicsManager;
	class Scene;

	/*
	Wrapper class for render dynamic lines
	*/
	class DebugRenderer
	{

	public:
		/// Constructor - see setOperationType() for description of argument.
		DebugRenderer(Scene& scene, float _fillAlpha);
		virtual ~DebugRenderer();

		std::list<VertexPair>& getLineVertices();
		std::list<VertexPair>& getTriangleVertices();
		
		std::list<int>& getLineIndices();
		std::list<int>& getTriangleIndices();


		/// Add a point to the point list
	//	void addPoint(const Ogre::Vector3 &p);
		/// Add a point to the point list
//		void addPoint(float x, float y, float z);

		/// Change the location of an existing point in the point list
//		void setPoint(unsigned short index, const Ogre::Vector3 &value);

		/// Remove all points from the point list
		void clear();

		/// Call this to update the hardware buffer after making changes.
		void update();
		

	private:

		float m_fillAlpha;

		GraphicsManager& m_GraphicsManager;
		//modify only in renderthread!
	//	DynamicLines* __t_DynamicLines;
		Ogre::ManualObject* _t_manualObject;
		Ogre::ObjectMemoryManager* _t_ObjectMemoryManager;

		bool _swapBuffer;

		//std::vector<Ogre::Vector3> _PointsBuf1;
		//std::vector<Ogre::Vector3> _PointsBuf2;

		std::list<VertexPair> lineVertices1, triangleVertices1;
		std::list<int> lineIndices1, triangleIndices1;

		std::list<VertexPair> lineVertices2, triangleVertices2;
		std::list<int> lineIndices2, triangleIndices2;
	};

} // namespace XE





