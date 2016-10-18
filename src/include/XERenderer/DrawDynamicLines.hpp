
#ifndef __DRAWDYNAMICLINES_HPP__
#define __DRAWDYNAMICLINES_HPP__

//#include <Ogre/OgreMain/include/OgreId.h>
#include <vector>

namespace Ogre
{
	class ObjectMemoryManager;
	class Vector3;
}

namespace XE
{
	class GraphicsManager;
	class Scene;
	class DynamicLines;

	/*
		Wrapper class for render dynamic lines
	*/
class DrawDynamicLines 
{

public:
  /// Constructor - see setOperationType() for description of argument.
	DrawDynamicLines(Scene& scene);
	virtual ~DrawDynamicLines();

  /// Add a point to the point list
  void addPoint(const Ogre::Vector3 &p);
  /// Add a point to the point list
  void addPoint(float x, float y, float z);

  /// Change the location of an existing point in the point list
  void setPoint(unsigned short index, const Ogre::Vector3 &value);

  /// Remove all points from the point list
  void clear();

  /// Call this to update the hardware buffer after making changes.
  void update();

private:
	bool m_rendererisDone;
	GraphicsManager& m_GraphicsManager;
	//modify only in renderthread!
	DynamicLines* __t_DynamicLines;
	Ogre::ObjectMemoryManager* _t_ObjectMemoryManager;

	bool _swapBuffer;
	std::vector<Ogre::Vector3> _PointsBuf1;
	std::vector<Ogre::Vector3> _PointsBuf2;
};

} // namespace XE

#endif // __DRAWDYNAMICLINES_HPP__





