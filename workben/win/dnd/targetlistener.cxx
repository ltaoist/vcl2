/* comment */
#include "targetlistener.hxx"
#include <com/sun/star/datatransfer/dnd/DNDConstants.hpp>
#include <com/sun/star/datatransfer/DataFlavor.hpp>

using namespace com::sun::star::datatransfer::dnd::DNDConstants;
using namespace com::sun::star::datatransfer;

DropTargetListener::DropTargetListener(HWND hEdit):m_hEdit( hEdit)
{
}
DropTargetListener::~DropTargetListener()
{
}

void SAL_CALL DropTargetListener::disposing( const EventObject& Source )
        throw(RuntimeException)
{

}

void SAL_CALL DropTargetListener::drop( const DropTargetDropEvent& e )
    throw(RuntimeException)
{
    e.Context->rejectDrop();

    DataFlavor flavor( OUString(OUString("text/plain;charset=windows-1252")),
        OUString(L"Text plain"), cppu::UnoType<Sequence<sal_Int8>>::get() );

    Any anyData= e.Transferable->getTransferData( flavor);
    Sequence<sal_Int8> seq= *( Sequence<sal_Int8>*)anyData.getValue();
    SendMessage( m_hEdit, WM_SETTEXT, 0, (LPARAM) seq.getConstArray() );
}

void SAL_CALL DropTargetListener::dragEnter( const DropTargetDragEnterEvent& dtde )
     throw(RuntimeException)
{
    //If one drags something that is not moveable
    if( !(dtde.SourceActions & dtde.DropAction) )
        dtde.Context->acceptDrag( ACTION_COPY);
}

void SAL_CALL DropTargetListener::dragExit( const DropTargetEvent& dte )
     throw(RuntimeException)
{
}

void SAL_CALL DropTargetListener::dragOver( const DropTargetDragEvent& dtde )
     throw(RuntimeException)
{
    if( !(dtde.SourceActions & dtde.DropAction) )
        dtde.Context->acceptDrag( ACTION_COPY);
}

void SAL_CALL DropTargetListener::dropActionChanged( const DropTargetDragEvent& dtde )
    throw(RuntimeException)
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
