/* comment */

#include <QtXAccessible.hxx>
#include <QtXAccessible.moc>

#include <QtFrame.hxx>
#include <QtTools.hxx>
#include <QtWidget.hxx>

#include <com/sun/star/accessibility/XAccessible.hpp>

#include <sal/log.hxx>
#include <utility>

using namespace css::accessibility;
using namespace css::uno;

QtXAccessible::QtXAccessible(Reference<XAccessible> xAccessible)
    : m_xAccessible(std::move(xAccessible))
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
