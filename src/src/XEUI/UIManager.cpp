//#include <XEUI/UIManager.hpp>
//#include <XEUI/UIPanel.hpp>
//
////#include <XEUI/Widgets/Navigation.hpp>
//
//#include "OgreException.h"
//
//namespace XE {
//
//UIManager::ElementID UIManager::m_last_guid = 0;
//
//using namespace std;
//
//UIManager::UIManager()  //: mNavigation(NULL)//PanelColors* panelColors)
//   // : mPanelColors(NULL)
//{
//  //  mSilverback = OGRE_NEW  Silverback();
//   // setPanelColors(panelColors);
//
//}
//
//
//UIManager::~UIManager()
//{
//    // Implicit delete of screens, screenRenderables and atlas
//  //  OGRE_DELETE mSilverback;
//}
//
//UIManager::ElementID UIManager::GetGUID() {
//	return ++m_last_guid;
//}
//
////Silverback* UIManager::getSilverback()
////{
////    return mSilverback;
////}
//
////
//// ScreenRenderables methods (2D Screens rendered in 3D)
////
//
//
////WLayer* UIManager::getLayer(const Ogre::String& screenRenderableName,
////                                const Ogre::String& layerName)
////{
////    if (mScreenRenderables[screenRenderableName] != NULL)
////        return mScreenRenderables[screenRenderableName]->mLayers[layerName];
////    
////    return NULL;
////}
////
//////Layer* UIManager::getLayer(Screen* screen, Ogre::String layer)
//////{
//////	std::map<String, XEUIScreen*>::iterator i;
//////	for(i = mScreens.begin(); i != mScreens.end(); i++)
//////		return getLayer(i->first, layer);
//////	return nullptr;
//////}
////
////
////WLayer* UIManager::getLayer(WScreenRenderable* screenRenderable,
////                                const Ogre::String& layerName)
////{
////	map<Ogre::String, XEUIScreenRenderable*>::iterator it =
////        mScreenRenderables.begin();
////
////    for (; it != mScreenRenderables.end(); ++it)
////        if (it->second->mScreenRenderable == screenRenderable)
////            return getLayer(it->first, layerName);
////
////    return NULL;
////}
////
////
////WLayer* UIManager::createLayer(WScreenRenderable* screenRenderable,
////                                   const Ogre::String& layerName)
////{
////    // Tests if already exists
////    Layer* layer = getLayer(screenRenderable, layerName);
////    if (layer != NULL)
////        return layer;
////
////	map<Ogre::String, XEUIScreenRenderable*>::iterator it =
////        mScreenRenderables.begin();
////
////    // Try to find the screenRenderable
////    for (; it != mScreenRenderables.end(); ++it)
////        if (it->second->mScreenRenderable == screenRenderable)
////        {
////            Layer* layer = screenRenderable->createLayer(1);
////            it->second->mLayers[layerName] = layer;
////            return layer;
////        }
////
////    return NULL;
////}
////
////
////Layer* UIManager::createLayer(const Ogre::String& screenRenderableName,
////                                   const Ogre::String& layerName)
////{
////    // Tests if already exists
////    Layer* layer = getLayer(screenRenderableName, layerName);
////    if (layer != NULL)
////        return layer;
////
////    // Try to find the screenRenderable
////    ScreenRenderable* screenR = 
////        mScreenRenderables[screenRenderableName]->mScreenRenderable;
////
////    if (screenR != NULL)
////    {
////        Layer* layer = screenR->createLayer();
////
////        mScreenRenderables[screenRenderableName]->mLayers[layerName] = layer;
////        return layer;
////    }
////
////    return NULL;
////}
//
////Layer* UIManager::createLayer(Screen* screen, Ogre::String layer)
////{
////	Layer* lyr = getLayer(screen, layer);
////	if(lyr != nullptr)
////		return lyr;
////
////		std::map<String, XEUIScreen*>::iterator i;
////		for(i = mScreens.begin(); i != mScreens.end(); i++)
////			if(i->second->mScreen == screen)
////			{
////				i->second->mLayers[layer] = i->second->mScreen->createLayer(i->second->mLayers.size());
////				return i->second->mLayers[layer];
////			}
////	return nullptr;
////}
//
//
////ScreenRenderable* UIManager::createScreenRenderable(const Ogre::Vector2& pos, 
////                                                         const Ogre::String& atlasName, 
////                                                         const Ogre::String& name, 
////														 Ogre::ObjectMemoryManager* objManager)
////{
////    if (!hasAtlas(atlasName))
////        loadAtlas(atlasName);
////
////    mScreenRenderables[name] = OGRE_NEW_T ( XEUIScreenRenderable(
////		mSilverback->createScreenRenderable(pos, atlasName, objManager)), Ogre::MEMCATEGORY_GENERAL);
////
////    return mScreenRenderables[name]->mScreenRenderable;
////}
////    
////
////ScreenRenderable* UIManager::getScreenRenderable(const Ogre::String& name)
////{
////    if (mScreenRenderables[name] != NULL)
////        return mScreenRenderables[name]->mScreenRenderable;
////
////    return NULL;
////}
//
//
////
//// Screens methods (2D screen)
////
//
//
////Layer* UIManager::getLayerScreen(const Ogre::String& screenName, 
////                                      const Ogre::String& layerName)
////{
////    if (mScreens[screenName] != 0)
////        return mScreens[screenName]->mLayers[layerName];
////
////    return NULL;
////}
////
////
////Layer* UIManager::getLayerScreen(Screen* screen, 
////                                      const Ogre::String& layerName)
////{
////	map<Ogre::String, XEUIScreen*>::iterator it = mScreens.begin();
////
////    for (; it != mScreens.end(); ++it)
////        if (it->second->mScreen == screen)
////            return getLayerScreen(it->first, layerName);
////
////    return NULL;
////}
////
////
////Layer* UIManager::createLayerScreen(Screen* screen, 
////                                         const Ogre::String& layerName)
////{
////    // Tests if already exists
////    Layer* layer = getLayerScreen(screen, layerName);
////    if (layer != NULL)
////        return layer;
////
////	map<Ogre::String, XEUIScreen*>::iterator it = mScreens.begin();
////
////    // Try to find the screen
////    for (; it != mScreens.end(); ++it)
////        if (it->second->mScreen == screen)
////        {
////            Layer* layer = screen->createLayer(1);
////            it->second->mLayers[layerName] = layer;
////            return layer;
////        }
////
////    return NULL;
////}
////
////
////Layer* UIManager::createLayerScreen(const Ogre::String& screenName, 
////                                         const Ogre::String& layerName)
////{
////    // Tests if already exists
////    Layer* layer = getLayerScreen(screenName, layerName);
////    if (layer != NULL)
////        return layer;
////
////    // Try to find the screen
////    Screen* screen = mScreens[screenName]->mScreen;
////
////    if (screen != NULL)
////    {
////        Layer* layer = screen->createLayer();
////
////        mScreens[screenName]->mLayers[layerName] = layer;
////        return layer;
////    }
////
////    return NULL;
////}
////
////
////Screen* UIManager::createScreen( Ogre::Viewport* vp,
////                                     const Ogre::String& atlasName, 
////                                     const Ogre::String& name )
////{
////    if (!hasAtlas( atlasName ))
////        loadAtlas( atlasName );
////
////	std::map<Ogre::String, XEUIScreen*>::iterator it = mScreens.find(name);
////
////	//Screen already exist then delete the old
////	if( it != mScreens.end() )
////		mScreens.erase( it ); //todo leak!??
////
////	mScreens[name] = OGRE_NEW_T(XEUIScreen(mSilverback->createScreen(vp, atlasName)), Ogre::MEMCATEGORY_GENERAL);
////
////    return mScreens[ name ]->mScreen;
////}
////
////
////Screen* UIManager::getScreen( const Ogre::String& name )
////{
////    if ( mScreens[ name ] != NULL )
////        return mScreens[ name ]->mScreen;
////    return NULL;
////}
//
//
//bool UIManager::injectMouseMoved( const  Ogre::Real& x, const  Ogre::Real& y, const Ogre::uint16& grp )
//{
//  //  mInternalMousePos = Ogre::Vector2(x, y);
// //   mMousePointer->position(mInternalMousePos);
//
//    // Let's actualize the "over" for each elements
//	/*mUIPanelVectorIt =  mUIPanelVector.begin();
//	for (;mUIPanelVectorIt != mUIPanelVector.end();++mUIPanelVectorIt)
//		if( (*mUIPanelVectorIt)->getGrp() == grp ) (*mUIPanelVectorIt)->injectMouseMoved(x, y);*/
//    
//  /*  for (size_t i=0; i < mPanelElements.size(); i++)
//        mPanelElements[i]->isOver(mInternalMousePos);*/
//
//    return true;
//}
//
//bool UIManager::pointSelectStart(Ogre::Vector2 point)
//{
//	/*mUIPanelVectorIt =  mUIPanelVector.begin();
//	for (;mUIPanelVectorIt != mUIPanelVector.end();++mUIPanelVectorIt)
//	{
//		if ((*mUIPanelVectorIt)->isEnabled())
//			(*mUIPanelVectorIt)->pointSelectStart(point);
//	}
//*/
//	 return true;
//}
//
//bool UIManager::pointSelectEnd(Ogre::Vector2 point)
//{
//	//mUIPanelVectorIt =  mUIPanelVector.begin(); //collides with destroy panel iterartor??
//	//while (mUIPanelVectorIt != mUIPanelVector.end())
//	//{
//	//	if((*mUIPanelVectorIt)->isEnabled())
//	//		(*mUIPanelVectorIt)->pointSelectEnd(point);
//
//	//	if ((*mUIPanelVectorIt)->isDestroying())
//	//	{
//	//		//mScreens[""]->mScreen->destroy();
//	////todo		destroyLayer( "WorldState", (*mUIPanelVectorIt)->getName() );
//
//	//		OGRE_DELETE *mUIPanelVectorIt;
//	//		*mUIPanelVectorIt = nullptr;
//	//		mUIPanelVectorIt = mUIPanelVector.erase( mUIPanelVectorIt );
//	//	}
//	//	else 
//	//		++mUIPanelVectorIt;
//	//}
//
//	 return true;
//}
//
////void UIManager::addUIPanel( UIPanel* uiPanel )
////{
////	//delete old Panel if already exists
////
////	//mUIPanelVectorIt = mUIPanelVector.begin();
////	//while (mUIPanelVectorIt != mUIPanelVector.end())
////	//{
////	//	if ( (*mUIPanelVectorIt)->getName() == uiPanel->getName()
////	//		&& (*mUIPanelVectorIt)->getGrp() == uiPanel->getGrp() ) 
////	//	{	
////	//		mUIPanelVectorIt = mUIPanelVector.erase( mUIPanelVectorIt );
////	//	}
////	//	else 
////	//		++mUIPanelVectorIt;
////	//}
////
////	mUIPanelVector.push_back(uiPanel);
////	//mUIPanelVectorIt = mUIPanelVector.begin();
////}
////
////UIPanel* UIManager::getUIPanel( const Ogre::String& panelName, const Ogre::uint16& group )
////{
////	/*vector<UIPanel*>::iterator it = mUIPanelVector.begin();
////	for (;it != mUIPanelVector.end();it++)
////	{
////		if ( (*it)->getName() == panelName
////			&& (*it)->getGrp() == group ) 
////			return (*it);
////	}
////
////	OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
////				"Could not find the Panel " + panelName, "UIManager::getUIPanel" );*/
////
////	return nullptr;
////}
////
////
////void UIManager::destroyLayer(const Ogre::String& screenName, const Ogre::String& layerName)
////{
////	 // Tests if already exists
//// //   WLayer* layer = getLayerScreen(screenName, layerName);
//// //   if (layer == NULL)
////	//	return;
////
////	//    // Try to find the screen
//// //   WScreen* screen = mScreens[screenName]->mScreen;
////
//// //   if (screen == NULL)
////	//	return;
////
////	//mScreens[screenName]->mLayers.erase(layerName);
////
//// //   screen->destroy(layer);
////}
////
////void UIManager::destroyUIPanel( UIPanel* panel )
////{
////	//for(mUIPanelVectorIt = mUIPanelVector.begin();mUIPanelVectorIt != mUIPanelVector.end();++mUIPanelVectorIt )
////	//{
////	//	if ( (*mUIPanelVectorIt) == panel ) 
////	//	{
////	//		destroyLayer( "WorldState", panel->getName() );
////
////	//		OGRE_DELETE *mUIPanelVectorIt;
////	//		*mUIPanelVectorIt = nullptr;
////	//		mUIPanelVectorIt = mUIPanelVector.erase( mUIPanelVectorIt );
////
////	//		mUIPanelVectorIt = mUIPanelVector.begin();
////	//		return;
////	//	}
////	//}
////}
////
////void UIManager::destroyUIPanel( const Ogre::String& panelName )
////{
//////	mUIPanelVectorIt = mUIPanelVector.begin();
//////	while (mUIPanelVectorIt != mUIPanelVector.end())
//////	{
//////		if ( (*mUIPanelVectorIt)->_destroy ) 
//////		{
//////			OGRE_DELETE (*mUIPanelVectorIt);
//////			*mUIPanelVectorIt = nullptr;
//////			mUIPanelVectorIt = mUIPanelVector.erase( mUIPanelVectorIt );
//////
//////			
////////			destroyLayer( "WorldState", (*mUIPanelVectorIt)->getName() );
//////		}
//////		else 
//////			++mUIPanelVectorIt;
//////	}
//////	mUIPanelVectorIt = mUIPanelVector.begin();
//////
////	mUIPanelVectorIt = mUIPanelVector.begin();
////	while (mUIPanelVectorIt != mUIPanelVector.end())
////	{
////		//if ( (*mUIPanelVectorIt)->getName() == panelName ) 
////		//{
////		//	//mScreens[""]->mScreen->destroy();
////		//	destroyLayer( "WorldState", panelName );
////
////		//	OGRE_DELETE *mUIPanelVectorIt;
////		//	*mUIPanelVectorIt = nullptr;
////		//	mUIPanelVectorIt = mUIPanelVector.erase( mUIPanelVectorIt );
////
////		//	mUIPanelVectorIt = mUIPanelVector.begin();
////		//	return;
////		//}
////		//else 
////			++mUIPanelVectorIt;
////	}
////	
////}
////
//// General methods
////
//
//
////bool UIManager::hasAtlas(const Ogre::String& name)
////{
////    for (size_t i=0; i < mAtlas.size(); i++)
////        if (mAtlas[i] == name)
////            return true;
////    return false;
////}
//
//
////void UIManager::loadAtlas(const Ogre::String& name)
////{
////    //mSilverback->loadAtlas(name);
////    //mAtlas.push_back(name);
////}
//
////ElementStyle* UIManager::addStyle(StyleType type, ElementStyle* elementStyle) {
////
////	return mStyles[type] = elementStyle;
////}
//
//
////ElementStyle* UIManager::getStyle(StyleType type) {
////		
////		map<StyleType, ElementStyle*>::iterator it = mStyles.find(type);
////
////		if(it != mStyles.end())
////			return mStyles[type];
////		else
////			return mStyles[S_Default];
////}
//
//void UIManager::selectOveredItem()
//{
//	//for (;mUIPanelVectorIt != mUIPanelVector.end();)
//	//{	
//	//	if( (*mUIPanelVectorIt)->getName() == mCurrentPanelName )
//	//		(*mUIPanelVectorIt)->selectOveredItem();
//
//	//	if((*mUIPanelVectorIt)->_destroy)
//	//	{
//	//		//mScreens[""]->mScreen->destroy();
//	//		destroyLayer( "WorldState", (*mUIPanelVectorIt)->getName() );
//
//	//		OGRE_DELETE *mUIPanelVectorIt;
//	//		mUIPanelVectorIt = mUIPanelVector.erase( mUIPanelVectorIt );
//	//		//*mUIPanelVectorIt = nullptr;
//	//	}
//	//	else 
//	//		++mUIPanelVectorIt;
//	//}
//}
//
//bool UIManager::makeNextItemOver()
//{
//	//if( mCurrentPanelName.empty() )
//	//	if(  mUIPanelVector.size() > 0 )
//	//		mCurrentPanelName = mUIPanelVector[0]->getName(); // set first panel as actual
//	//	else
//	//		return false; //no Panels
//
//	//// next Panel
//	//mUIPanelVectorIt =  mUIPanelVector.begin(); //collides with destroy panel iterartor??
//	//for (;mUIPanelVectorIt != mUIPanelVector.end();++mUIPanelVectorIt)
//	//{
//	//	if( (*mUIPanelVectorIt)->getName() == mCurrentPanelName )
//	//	{
//	//		if((*mUIPanelVectorIt)->makeNextItemOver()) //Current Panel Next Item
//	//			return true;		
//	//		else
//	//		{
//	//			++mUIPanelVectorIt;
//	//			if(mUIPanelVectorIt != mUIPanelVector.end())
//	//			{
//	//				mCurrentPanelName = (*mUIPanelVectorIt)->getName();
//	//				return (*mUIPanelVectorIt)->makeNextItemOver();  // Next Panel First Item	
//	//			}
//	//			else
//	//				return false;
//	//		}
//	//	}
//	//}
//	return nullptr;
//}
//
//bool UIManager::makePrevItemOver()
//{
//	//if( mCurrentPanelName.empty() )
//	//	if(  mUIPanelVector.size() > 0 )
//	//		mCurrentPanelName = mUIPanelVector[0]->getName(); // set first panel as actual
//	//	else
//	//		return false; //no Panels
//
//	//// next Panel
//	//mUIPanelVectorIt =  mUIPanelVector.end(); //collides with destroy panel iterartor??
//	//for (;mUIPanelVectorIt != mUIPanelVector.begin();)
//	//{
//	//	--mUIPanelVectorIt; // Unfortunately, you now need this here
//
//	//	if( (*mUIPanelVectorIt)->getName() == mCurrentPanelName )
//	//	{
//	//		if((*mUIPanelVectorIt)->makePrevItemOver()) //Current Panel Next Item
//	//			return true;
//	//		else
//	//		{
//	//			//--mUIPanelVectorIt;
//	//			if(mUIPanelVectorIt != mUIPanelVector.begin())
//	//			{
//	//				mCurrentPanelName = (*mUIPanelVectorIt)->getName();
//	//				return (*mUIPanelVectorIt)->makePrevItemOver();  // Next Panel First Item
//	//			}
//	//			else
//	//				return false;
//	//		}
//	//	}
//	//}
//	return nullptr;
//}
//
////void UIManager::windowResized(Ogre::RenderWindow* rw)
////{
////	mUIPanelVectorIt =  mUIPanelVector.begin(); //collides with destroy panel iterartor??
////	for (;mUIPanelVectorIt != mUIPanelVector.end();++mUIPanelVectorIt)
////	{
////		(*mUIPanelVectorIt)->windowResized(rw);
////	}
////}
//
//
////void UIManager::addDesktop(Desktop::Ptr desktop)
////{
////	m_DesktopList.push_back(desktop);
////}
////
////void UIManager::update(const Ogre::Real& timeElapsed)
////{
////	for (auto& var : m_DesktopList)
////	{
////		var->Update(timeElapsed);
////	}
////	//for (unsigned int i(0); i < mUIPanelVector.size(); ++ i)
//// //{
//// //  /* if (mUIPanelVector[i]->_destroy)
//// //    {
//// //       delete mUIPanelVector[i];
//// //       mUIPanelVector.erase(mUIPanelVector.begin() + (i --));
//// //    }*/
//// //}
////}
//
//void UIManager::destroyStyles()
//	{
//
//	//mStyles.clear();
//
//	//	for(map<StyleType, ElementStyle>::iterator it = mStyles.begin(); it != mStyles.end(); it++)
//	//	{
//	//	 OGRE_DELETE it->second;
//	//	//	it->second = nullptr;
//	//	}
//
//	//	mStyles.clear();
//	}
//
//void UIManager::destroyScreenRenderable(const Ogre::String& screenRenderableName)
//{
//    // Will implicitly destroy its layers
//  /*  mSilverback->destroyScreenRenderable(mScreenRenderables[screenRenderableName]->mScreenRenderable);
//    mScreenRenderables.erase(screenRenderableName);*/
//}
//
//
//void UIManager::destroyScreenRenderable(WScreenRenderable* screenRenderable)
//{
//	//map<Ogre::String, XEUIScreenRenderable*>::iterator it =
// //       mScreenRenderables.begin();
//
// //   for (; it != mScreenRenderables.end(); ++it)
// //       if (it->second->mScreenRenderable == screenRenderable)
// //       {
// //           destroyScreenRenderable(it->first);
// //           break;
// //       }
//}
//
//
////void UIManager::destroyScreen(const Ogre::String& screenName)
////{
////    // Will implicitly destroy its layers
////    //mSilverback->destroyScreen(mScreens[screenName]->mScreen);
////
////    //mScreens.erase(screenName);
////}
////
////
////void UIManager::destroyScreen(WScreen* screen)
////{
////	map<Ogre::String, WScreen*>::iterator it = m_screens.begin();
////
////	//for (auto i : m_screens) // access by reference, the type of i is int&
////	//	i->second->
////
////	for (auto&& kv : m_screens) {
////		//std::cout << kv.first << " has value " << kv.second << std::endl;
////	}
////
////	/*for (; it != m_screens.end(); ++it)
////        if (it->second->mScreen == screen)
////        {
////            destroyScreen(it->first);
////            break;
////        }*/
////}
//
//
////void UIManager::setPanelColors(PanelColors* panelColors)
////{
////    mPanelColors = panelColors;
////}
////
////
////PanelColors* UIManager::getPanelColors()
////{
////    return mPanelColors;
////}
//
//
//} //namespace XE
