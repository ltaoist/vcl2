/* comment */
#include "sourcelistener.hxx"

DragSourceListener::DragSourceListener()
{
}
DragSourceListener::~DragSourceListener()
{
}

void SAL_CALL DragSourceListener::disposing( const EventObject& Source )
        throw(RuntimeException)
{
}

void SAL_CALL DragSourceListener::dragDropEnd( const DragSourceDropEvent& dsde )
    throw(RuntimeException)
{
}

void SAL_CALL DragSourceListener::dragEnter( const DragSourceDragEvent& dsde )
    throw(RuntimeException)
{
}

void SAL_CALL DragSourceListener::dragExit( const DragSourceEvent& dse )
    throw(RuntimeException)
{
}

void SAL_CALL DragSourceListener::dragOver( const DragSourceDragEvent& dsde )
    throw(RuntimeException)
{
}

void SAL_CALL DragSourceListener::dropActionChanged( const DragSourceDragEvent& dsde )
    throw(RuntimeException)
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
