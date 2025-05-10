/* comment */
#include "targetdropcontext.hxx"

using namespace ::com::sun::star::datatransfer::dnd;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

TargetDropContext::TargetDropContext(DropTarget* p)
{
    m_pDropTarget = p;
    p->acquire();
}

TargetDropContext::~TargetDropContext() { m_pDropTarget->release(); }

void SAL_CALL TargetDropContext::acceptDrop(sal_Int8 dropOperation)
{
    m_pDropTarget->_acceptDrop(dropOperation, static_cast<XDropTargetDropContext*>(this));
}

void SAL_CALL TargetDropContext::rejectDrop()
{
    m_pDropTarget->_rejectDrop(static_cast<XDropTargetDropContext*>(this));
}

void SAL_CALL TargetDropContext::dropComplete(sal_Bool success)
{
    m_pDropTarget->_dropComplete(success, static_cast<XDropTargetDropContext*>(this));
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
