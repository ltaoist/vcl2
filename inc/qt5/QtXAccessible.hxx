/* comment */

#pragma once

#include <vclpluginapi.h>

#include <QtCore/QObject>

#include <com/sun/star/accessibility/XAccessible.hpp>

#include <vcl/window.hxx>

class QtFrame;
class QtWidget;

// Wrapper class to hold a css::accessibility::XAccessible object
// while being able to pass it as a QObject
class QtXAccessible : public QObject
{
    Q_OBJECT

public:
    QtXAccessible(css::uno::Reference<css::accessibility::XAccessible> xAccessible);

    /** Reference to the XAccessible.
      * This is cleared once it has been passed to the QtAccessibleWidget,
      * which then keeps an own reference and takes care of all required
      * access to the XAccessible for the Qt a11y bridge. */
    css::uno::Reference<css::accessibility::XAccessible> m_xAccessible;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
