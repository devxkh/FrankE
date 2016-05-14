#ifndef Gui3DFunctorBase_H
#define Gui3DFunctorBase_H

#include <Ogre/OgreMain/include/Ogre.h>

namespace XE {

	class PanelElement;
/*! class. FunctorBase
    desc.
        Abstract interface that will be used for all functor
        object for callbacks
*/
class FunctorBase : public Ogre::GeneralAllocatedObject 
{
public:
    virtual ~FunctorBase() {};

    virtual bool operator()(PanelElement*) = 0;
};


} // namespace XE

#endif