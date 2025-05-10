/* comment */
#pragma once

#include <cppuhelper/implbase.hxx>
#include <com/sun/star/datatransfer/dnd/XDropTargetDropContext.hpp>

#include <win/dnd_target.hxx>

using namespace ::com::sun::star::datatransfer::dnd;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

class TargetDropContext : public WeakImplHelper<XDropTargetDropContext>
{
    // calls to the functions of XDropTargetDropContext are delegated
    // to non-interface functions of m_pDropTarget
    DropTarget* m_pDropTarget;

public:
    explicit TargetDropContext(DropTarget* pTarget);
    ~TargetDropContext() override;
    TargetDropContext(const TargetDropContext&) = delete;
    TargetDropContext& operator=(const TargetDropContext&) = delete;

    // XDropTargetDragContext
    virtual void SAL_CALL acceptDrop(sal_Int8 dropOperation) override;
    virtual void SAL_CALL rejectDrop() override;

    // XDropTargetDropContext (inherits XDropTargetDragContext)
    virtual void SAL_CALL dropComplete(sal_Bool success) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
