/* comment */
#pragma once
#include <com/sun/star/accessibility/XAccessibleEventListener.hpp>
#include <cppuhelper/implbase.hxx>

#include "a11yfocustracker.hxx"
#include "osxvcltypes.h"
#include <set>
#include <com/sun/star/awt/Rectangle.hpp>

class AquaA11yEventListener
    : public ::cppu::WeakImplHelper<css::accessibility::XAccessibleEventListener>
{
public:
    AquaA11yEventListener(id wrapperObject, sal_Int16 role);
    virtual ~AquaA11yEventListener() override;

    // XEventListener
    virtual void SAL_CALL disposing(const css::lang::EventObject& Source) override;

    // XAccessibleEventListener
    virtual void SAL_CALL
    notifyEvent(const css::accessibility::AccessibleEventObject& aEvent) override;

private:
    const id m_wrapperObject;
    const sal_Int16 m_role;
    css::awt::Rectangle m_oldBounds;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
