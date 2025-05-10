/* comment */
#pragma once

#include <cppuhelper/implbase.hxx>
#include <com/sun/star/datatransfer/dnd/XDropTargetDragContext.hpp>
#include <com/sun/star/datatransfer/DataFlavor.hpp>

#include <win/dnd_target.hxx>

using namespace ::com::sun::star::datatransfer;
using namespace ::com::sun::star::datatransfer::dnd;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

class TargetDragContext : public WeakImplHelper<XDropTargetDragContext>
{
    // some calls to the functions of XDropTargetDragContext are delegated
    // to non-interface functions of m_pDropTarget
    DropTarget* m_pDropTarget;

public:
    explicit TargetDragContext(DropTarget* pTarget);
    ~TargetDragContext() override;
    TargetDragContext(const TargetDragContext&) = delete;
    TargetDragContext& operator=(const TargetDragContext&) = delete;

    virtual void SAL_CALL acceptDrag(sal_Int8 dragOperation) override;
    virtual void SAL_CALL rejectDrag() override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
