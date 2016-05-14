/*
 * =====================================================================================
 *
 *       Filename:  BtOgreExtras.h
 *
 *    Description:  Contains the Ogre Mesh to Bullet Shape converters.
 *
 *        Version:  1.0
 *        Created:  27/12/2008 01:45:56 PM
 *
 *         Author:  Nikhilesh (nikki)
	modified: Nuke
		
 *
 * =====================================================================================
 */

#ifndef __DYNAMICRENDERABLE_HPP__
#define __DYNAMICRENDERABLE_HPP__


#include <Ogre/OgreMain/include/OgreSimpleRenderable.h>

#include <Ogre/OgreMain/include/OgreCamera.h>
#include <Ogre/OgreMain/include/OgreHardwareBufferManager.h>
#include <Ogre/OgreMain/include/OgreMaterialManager.h>
#include <Ogre/OgreMain/include/OgreTechnique.h>
#include <Ogre/OgreMain/include/OgrePass.h>
#include <Ogre/OgreMain/include/OgreSceneNode.h>

#include <Ogre/OgreMain/include/OgreLogManager.h>


#include <Ogre/OgreMain/include/OgreRenderable.h>
#include <Ogre/OgreMain/include/Vao/OgreVertexBufferPacked.h>

namespace XE
{

//typedef std::vector<Ogre::Vector3> Vector3Array;


//From here on its debug-drawing stuff. ------------------------------------------------------------------

	class DynamicRenderable : public Ogre::Renderable , public Ogre::MovableObject //: public Ogre::v1::SimpleRenderable
{
public:
  /// Constructor
	DynamicRenderable(Ogre::IdType id, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);
  /// Virtual destructor
  virtual ~DynamicRenderable();

  /** Initializes the dynamic renderable.
   @remarks
      This function should only be called once. It initializes the
      render operation, and calls the abstract function
      createVertexDeclaration().
   @param operationType The type of render operation to perform.
   @param useIndices Specifies whether to use indices to determine the
          vertices to use as input. */
  void initialize(Ogre::v1::RenderOperation::OperationType operationType,
                  bool useIndices);

  /// Implementation of Ogre::SimpleRenderable
  virtual float getBoundingRadius(void) const;
  /// Implementation of Ogre::SimpleRenderable
  virtual float getSquaredViewDepth(const Ogre::Camera* cam) const;

protected:
  /// Maximum capacity of the currently allocated vertex buffer.
  size_t mVertexBufferCapacity;
  /// Maximum capacity of the currently allocated index buffer.
  size_t mIndexBufferCapacity;

  /** Creates the vertex declaration.
   @remarks
      Override and set mRenderOp.vertexData->vertexDeclaration here.
      mRenderOp.vertexData will be created for you before this method
      is called. */
  virtual void createVertexDeclaration() = 0;

  /** Prepares the hardware buffers for the requested vertex and index counts.
   @remarks
      This function must be called before locking the buffers in
      fillHardwareBuffers(). It guarantees that the hardware buffers
      are large enough to hold at least the requested number of
      vertices and indices (if using indices). The buffers are
      possibly reallocated to achieve this.
   @par
      The vertex and index count in the render operation are set to
      the values of vertexCount and indexCount respectively.
   @param vertexCount The number of vertices the buffer must hold.

   @param indexCount The number of indices the buffer must hold. This
          parameter is ignored if not using indices. */
  void prepareHardwareBuffers(size_t vertexCount, size_t indexCount);

  /** Fills the hardware vertex and index buffers with data.
   @remarks
      This function must call prepareHardwareBuffers() before locking
      the buffers to ensure the they are large enough for the data to
      be written. Afterwards the vertex and index buffers (if using
      indices) can be locked, and data can be written to them. */
  virtual void fillHardwareBuffers() = 0;


  void getRenderOperation(Ogre::v1::RenderOperation& op);

  void getWorldTransforms(Ogre::Matrix4* xform) const;

  const Ogre::LightList& getLights(void) const;


  // MovableObject overrides
  /** @copydoc MovableObject::getMovableType. */
  const Ogre::String& getMovableType(void) const;


 // float * mVertexBufferCursor;
  float *mVertexBuffer;
  char * mIndexBufferCursor;

  Ogre::v1::RenderOperation::OperationType m_operationType;
  Ogre::AxisAlignedBox mBox;
  Ogre::VertexArrayObject* mVao;
  Ogre::VaoManager * mVaoManager;
  Ogre::v1::RenderOperation::OperationType mOperationType;
  Ogre::VertexElement2Vec mVertexElements;
  bool m32BitIndices;
  Ogre::String mName;
  size_t mIndices;
};

} // namespace XE

#endif // __DYNAMICRENDERABLE_HPP__





