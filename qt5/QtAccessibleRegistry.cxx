/* comment */

#include <QtAccessibleRegistry.hxx>
#include <QtXAccessible.hxx>

#include <cassert>

std::map<XAccessible*, QObject*> QtAccessibleRegistry::m_aMapping = {};

QObject* QtAccessibleRegistry::getQObject(css::uno::Reference<XAccessible> xAcc)
{
    if (!xAcc.is())
        return nullptr;

    // look for existing entry in the map
    auto entry = m_aMapping.find(xAcc.get());
    if (entry != m_aMapping.end())
        return entry->second;

    // create a new object and remember it in the map
    QtXAccessible* pQtAcc = new QtXAccessible(xAcc);
    m_aMapping.emplace(xAcc.get(), pQtAcc);
    return pQtAcc;
}

void QtAccessibleRegistry::insert(css::uno::Reference<XAccessible> xAcc, QObject* pQObject)
{
    assert(pQObject);
    m_aMapping.emplace(xAcc.get(), pQObject);
}

void QtAccessibleRegistry::remove(css::uno::Reference<XAccessible> xAcc)
{
    assert(xAcc.is());
    m_aMapping.erase(xAcc.get());
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
