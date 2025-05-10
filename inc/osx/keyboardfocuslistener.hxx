/* comment */
#ifndef INCLUDED_VCL_INC_OSX_KEYBOARDFOCUSLISTENER_HXX
#define INCLUDED_VCL_INC_OSX_KEYBOARDFOCUSLISTENER_HXX

#include <com/sun/star/accessibility/XAccessible.hpp>

#include <rtl/ref.hxx>
#include <salhelper/simplereferenceobject.hxx>

class KeyboardFocusListener : public salhelper::SimpleReferenceObject
{
public:
    virtual void
    focusedObjectChanged(const css::uno::Reference<css::accessibility::XAccessible>& xAccessible)
        = 0;
};

#endif // INCLUDED_VCL_INC_OSX_KEYBOARDFOCUSLISTENER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
