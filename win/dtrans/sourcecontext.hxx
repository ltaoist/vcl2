/* comment */#pragma once

#include <com/sun/star/datatransfer/dnd/XDragSourceContext.hpp>
#include <cppuhelper/compbase.hxx>
#include <cppuhelper/basemutex.hxx>

#include <win/dnd_source.hxx>

using namespace ::com::sun::star::datatransfer;
using namespace ::com::sun::star::datatransfer::dnd;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

// This class fires events to XDragSourceListener implementations.
// Of that interface only dragDropEnd and dropActionChanged are called.
// The functions dragEnter, dragExit and dragOver are not supported
// currently.
// An instance of SourceContext only lives as long as the drag and drop
// operation lasts.
class SourceContext : public cppu::BaseMutex, public WeakComponentImplHelper<XDragSourceContext>
{
    DragSource* m_pDragSource;
    Reference<XDragSource> m_dragSource;
    // the action ( copy, move etc)
    sal_Int8 m_currentAction;

public:
    SourceContext(DragSource* pSource, const Reference<XDragSourceListener>& listener);
    ~SourceContext() override;
    SourceContext(const SourceContext&) = delete;
    SourceContext& operator=(const SourceContext&) = delete;

    /// @throws RuntimeException
    virtual void addDragSourceListener(const Reference<XDragSourceListener>& dsl);
    /// @throws RuntimeException
    virtual void removeDragSourceListener(const Reference<XDragSourceListener>& dsl);
    virtual sal_Int32 SAL_CALL getCurrentCursor() override;
    virtual void SAL_CALL setCursor(sal_Int32 cursorId) override;
    virtual void SAL_CALL setImage(sal_Int32 imageId) override;
    virtual void SAL_CALL transferablesFlavorsChanged() override;

    // non - interface functions
    void fire_dragDropEnd(bool success, sal_Int8 byte);
    void fire_dropActionChanged(sal_Int8 dropAction, sal_Int8 userAction);
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
