
#ifndef Gui3DMemberFunction_H
#define Gui3DMemberFunction_H

#include <XEUI/FunctorBase.hpp>

namespace XE {


/*! class. FunctorBase
    desc.
        Create a function that callback a class member function
*/
template<typename T>
class MemberFunction : public FunctorBase
{
public:
    typedef bool(T::*MemberMethodType)(PanelElement*);

    MemberFunction(T* obj, MemberMethodType method)
    : mMethod(method), mObject(obj)
    {}

    virtual bool operator()(PanelElement* e)
    {
        if (mObject != NULL && mMethod != NULL)
            return (mObject->*mMethod)(e);
        return false;
    }

protected:
    MemberMethodType mMethod;
    T* mObject;
};


} // namespace XE

#endif