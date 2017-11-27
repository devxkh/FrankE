#pragma once

#include <XESystem/SystemConfig.hpp>
#include <Ogre/OgreMain/include/OgreVector3.h>

namespace Ogre
{
	class Item;
	class Node;
	class SceneNode;
}

namespace XE {

	class AnimationComponent;
	class GraphicsManager;
	class Scene;
	
	struct Renderable {

	public:

		Renderable( GraphicsManager& gmanager, Scene& scene, const void* fbData);
		~Renderable();

		void update(const void* fbData);
		
		void update(float delta);

		void createAnimations(AnimationComponent& animationComponent);

		void destoyItems();

		void setScale(const Ogre::Vector3& scale);
			
		void setWorldPosition(const Ogre::Vector3& pos);

		void setOrientation(const Ogre::Quaternion& rot);

		void setVisibility(const bool isVisible);
	
		bool isVisible();

		//void rotate(const  Ogre::Quaternion& q, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
		//void rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
		//void scale(const Ogre::Vector3& scale);
		//void setOrientation(const Ogre::Quaternion& q);

		//Ogre::Vector3& getPosition();
		//Ogre::Vector3& getScale();
		//Ogre::Quaternion& getOrientation();
		//Ogre::Quaternion& getDerivedOrientation(); //world

		//Ogre::Matrix4& getFullTransform();
		//Ogre::Vector3& getDerivedPosition();//world
		//Ogre::Vector3& getDerivedScale();//world

		Ogre::Vector3& getBonePosition(XE::Uint16 idx) {
			if (idx >= m_bonePositions.size()){//Exception!!! 
			}
			return m_bonePositions[idx]; }

		//void setPosition(const Ogre::Vector3& pos);

		void destroy();

		inline GraphicsManager& getGraphicsManager() { return m_GraphicsManager; }
		inline Scene& getScene() { return m_Scene; }
		inline XE::Uint16  getID() { return m_ID; }

		Ogre::Item* _t_getEntPtr() { return _t_OgreItemPtr; }
		Ogre::SceneNode* _t_getNodePtr() { return _t_OgreEntitySceneNodePtr; }
		void _t_setNodePtr(Ogre::SceneNode* ptrs) { _t_OgreEntitySceneNodePtr = ptrs; }
		void _t_setEntPtr(Ogre::Item* ptr) { _t_OgreItemPtr = ptr; }

		//change only  in Renderthread!!!
		Ogre::Item* _t_OgreItemPtr;
		Ogre::SceneNode* _t_OgreEntitySceneNodePtr;

		GraphicsManager& m_GraphicsManager;

		void _t_update();

		//void setBlendmode();

		bool isDirty;

	protected:


		Scene& m_Scene;
		XE::Uint16 m_ID;


		//Ogre::Vector3 m_worldPosition;
		//Ogre::Vector3 m_position;
		//Ogre::Vector3 m_worldScale;
		//Ogre::Vector3 m_scale;

		//Ogre::Quaternion m_orientation;
		//Ogre::Quaternion m_worldOrientation;
		//Ogre::Matrix4 m_transform;
		//Ogre::Matrix4 m_worldTransform;

	private:

		//Ogre::Item* _newItem;

		Ogre::Vector3 _t_LastPosition;
		Ogre::Vector3 _t_CurrentPosition;

		bool m_isVisible;
		Ogre::Vector3 m_scale;
		Ogre::Vector3 m_position;
		Ogre::Quaternion m_rotation;

		Ogre::HlmsDatablock *m_datablock;

		//change only in renderthread
		Ogre::v1::AnimationStateSet* _t_animations;

		void _t_createItem(const void* fbData);

		std::vector<Ogre::Vector3> m_bonePositions;
		//Ogre::Vector3 m_boneOnePos;
		//Ogre::Vector3 m_boneTwoPos;
		//Ogre::Vector3 m_boneThreePos;
		//Ogre::Vector3 m_boneFourPos;




	};
}