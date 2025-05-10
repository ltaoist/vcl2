/* comment */

#pragma once

#include <com/sun/star/accessibility/XAccessible.hpp>
#include <com/sun/star/accessibility/XAccessibleEventListener.hpp>
#include <com/sun/star/lang/EventObject.hpp>

#include "QtAccessibleWidget.hxx"

#include <cppuhelper/implbase.hxx>

class QtAccessibleEventListener final
    : public cppu::WeakImplHelper<css::accessibility::XAccessibleEventListener>
{
public:
    explicit QtAccessibleEventListener(QtAccessibleWidget* pAccessibleWidget);

    virtual void SAL_CALL
    notifyEvent(const css::accessibility::AccessibleEventObject& aEvent) override;

    virtual void SAL_CALL disposing(const css::lang::EventObject& Source) override;

private:
    QtAccessibleWidget* m_pAccessibleWidget;

    static void HandleStateChangedEvent(QAccessibleInterface* pQAccessibleInterface,
                                        const css::accessibility::AccessibleEventObject& rEvent);
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
