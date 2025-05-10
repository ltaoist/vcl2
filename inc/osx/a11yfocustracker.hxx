/* comment */
#pragma once

#include <com/sun/star/accessibility/XAccessible.hpp>

#include "keyboardfocuslistener.hxx"

#include <tools/link.hxx>
#include <vcl/vclevent.hxx>
#include <set>

namespace vcl { class Window; }
class ToolBox;
class DocumentFocusListener;


class AquaA11yFocusTracker
{

public:
    AquaA11yFocusTracker();

    ~AquaA11yFocusTracker();

    css::uno::Reference< css::accessibility::XAccessible > const & getFocusedObject() { return m_xFocusedObject; };

    // sets the currently focus object and notifies the FocusEventListener (if any)
    void setFocusedObject(const css::uno::Reference< css::accessibility::XAccessible >& xAccessible);

    // may evolve to add/remove later
    void setFocusListener(const rtl::Reference< KeyboardFocusListener >& aFocusListener) { m_aFocusListener = aFocusListener; };

protected:

    // received a WINDOW_GETFOCUS event for this window
    void window_got_focus(vcl::Window *pWindow);

    // received a TOOLBOX_HIGHLIGHT event for this window
    void toolbox_highlight_on(vcl::Window *pWindow);

    // received a TOOLBOX_HIGHLIGHTOFF event for this window
    void toolbox_highlight_off(vcl::Window const *pWindow);

    // received a TABPAGE_ACTIVATE event for this window
    void tabpage_activated(vcl::Window *pWindow);

    // received a MENU_HIGHLIGHT event for this window
    void menu_highlighted(const ::VclMenuEvent *pEvent);

    // toolbox items are widgets in gtk+ and Cocoa
    void notify_toolbox_item_focus(ToolBox *pToolBox);

    // toolbox item opened a floating window (e.g. color chooser)
    void toolbox_open_floater(vcl::Window *pWindow);

    // callback function for Application::addEventListener
    static void WindowEventHandler(void * pThis, VclSimpleEvent&);

private:
    // the accessible object that has the keyboard focus (if any)
    css::uno::Reference< css::accessibility::XAccessible > m_xFocusedObject;

    // the listener for focus events
    rtl::Reference< KeyboardFocusListener > m_aFocusListener;

    // the list of Windows that need deeper (focus) investigation
    std::set<VclPtr<vcl::Window>> m_aDocumentWindowList;

    // the link object needed for Application::addEventListener
    Link<VclSimpleEvent&,void> m_aWindowEventLink;

    // the UNO XAccessibilityEventListener for Documents and other non VCL objects
    const rtl::Reference< DocumentFocusListener > m_xDocumentFocusListener;
};

AquaA11yFocusTracker& TheAquaA11yFocusTracker();


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
