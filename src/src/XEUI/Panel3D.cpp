

#include <XEUI/Panel3D.hpp>

#include <XEUI/PanelElement.hpp>
//#include <XEUI/PanelColors.h> //todo !

namespace XE {


using namespace std;

Panel3D::Panel3D(UIManager* gui, 
				Ogre::SceneManager* sceneMgr,
				Ogre::ObjectMemoryManager* objManager,
				 Ogre::Real distanceFromPanel3DToInteractWith,
				const Ogre::String& atlasName,
				const Ogre::String& name, 
				const Ogre::uint16& grp )
             : UIPanel(gui, name, grp),
               mDistanceFromPanelToInteractWith(distanceFromPanel3DToInteractWith),
               mNode(NULL), mPanelCameraNode(NULL), mScreenRenderable(NULL)
{
 //   mScreenRenderable = 
 //       gui->createScreenRenderable(Ogre::Vector2(_size.x/100, _size.y/100), atlasName, name, objManager);

 //   mNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
 //   mNode->attachObject(mScreenRenderable);

 //   mPanelCameraNode = mNode->createChildSceneNode();
 //   mPanelCameraNode->setPosition(-1, 0, 7);
	//mPanelCameraNode->lookAt(mNode->getPosition(), Ogre::Node::TS_PARENT);
 //   
 //   mGUILayer = gui->createLayer(mScreenRenderable, name);
 //   
 //   _background = mGUILayer->createRectangle(0, 0, _size.x, _size.y);

	//ElementStyle* style = getStyle(S_Panel3D);

	//styleRectangle(_background,style,ES_Default);

 //   // Create an empty mouse pointer which follow the mouse cursor
 //   _mousePointer = mGUILayer->createRectangle(0, 0, 0, 0);
 //   showInternalMousePointer();
}


Panel3D::~Panel3D()
{
	for (PanelEleVector::iterator it =  mPanelElements.begin();it != mPanelElements.end();++it) 
	{
		delete *it;
		*it = NULL;
	}
	
	mPanelElements.clear();
	
    // Destroy all elements that had been created on the screen renderable
  //  mXEUI->destroyScreenRenderable(mScreenRenderable);
}


void Panel3D::setDistanceFromPanelToInteractWith( Ogre::Real distanceFromPanel3DToInteractWith)
{
    mDistanceFromPanelToInteractWith = distanceFromPanel3DToInteractWith;
}

void Panel3D::windowResized(Ogre::RenderWindow* rw)
{
	//todo
}

bool Panel3D::injectMouseMoved(const Ogre::Ray& ray)
{
	//todo komplett auskommentiert weil dependecy fehlt?


	//Ogre::Matrix4 transform;
 //   transform.makeTransform(mNode->getPosition(), mNode->getScale(), mNode->getOrientation());
 //  
	//Ogre::AxisAlignedBox aabb = mScreenRenderable->getBoundingBox();
 //   aabb.transform(transform);
	//pair<bool, Ogre::Real> result = Ogre::Math::intersects(ray, aabb);

 //   if (result.first == false)
 //   {
 //       unOverAllElements();
 //       return false;
 //   }

 //   Ogre::Vector3 a,b,c,d;
 //   Ogre::Vector2 halfSize = (_size/100) * 0.5f;
 //   a = transform * Ogre::Vector3(-halfSize.x,-halfSize.y,0);
 //   b = transform * Ogre::Vector3( halfSize.x,-halfSize.y,0);
 //   c = transform * Ogre::Vector3(-halfSize.x, halfSize.y,0);
 //   d = transform * Ogre::Vector3( halfSize.x, halfSize.y,0);
 //   
	//result = Ogre::Math::intersects(ray, c, b, a);
 //   if (result.first == false)
	//	result = Ogre::Math::intersects(ray, c, d, b);
 //   if (result.first == false)
 //   {
 //       unOverAllElements();
 //       return false;
 //   }
 //   if (result.second > mDistanceFromPanelToInteractWith)
 //   {
 //       unOverAllElements();
 //       return false;
 //   }

 //   Ogre::Vector3 hitPos = (ray.getOrigin() + (ray.getDirection() * result.second));
 //   Ogre::Vector3 localPos = transform.inverse() * hitPos;
 //   localPos.x += halfSize.x;
 //   localPos.y -= halfSize.y;
 //   localPos.x *= 100;
 //   localPos.y *= 100;
 //  
 //   // Cursor clip
	//localPos.x = Ogre::Math::Clamp< Ogre::Real>(localPos.x, 0, _size.x - 10);
	//localPos.y = Ogre::Math::Clamp< Ogre::Real>(-localPos.y, 0, _size.y - 18);

 //   mInternalMousePos = Ogre::Vector2(localPos.x, localPos.y);
 //   _mousePointer->position(mInternalMousePos);

 //   // Let's actualize the "over" for each elements
 //   for (size_t i=0; i < mPanelElements.size(); i++)
 //       mPanelElements[i]->isOver(mInternalMousePos);

    return true;
}


} // namespace XE