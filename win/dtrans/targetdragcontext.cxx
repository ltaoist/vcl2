/* comment */
#include "targetdragcontext.hxx"

TargetDragContext::TargetDragContext(DropTarget* p)
{
    m_pDropTarget = p;
    p->acquire();
}

TargetDragContext::~TargetDragContext() { m_pDropTarget->release(); }

void SAL_CALL TargetDragContext::acceptDrag(sal_Int8 dragOperation)
{
    m_pDropTarget->_acceptDrag(dragOperation, static_cast<XDropTargetDragContext*>(this));
}
void SAL_CALL TargetDragContext::rejectDrag()
{
    m_pDropTarget->_rejectDrag(static_cast<XDropTargetDragContext*>(this));
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
