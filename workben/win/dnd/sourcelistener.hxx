/* comment */
#pragma once

#include <cppuhelper/implbase.hxx>
#include <com/sun/star/datatransfer/dnd/XDragSourceListener.hpp>
#include <com/sun/star/datatransfer/dnd/DragSourceDropEvent.hpp>
#include <com/sun/star/datatransfer/dnd/DragSourceDragEvent.hpp>

using namespace ::com::sun::star::datatransfer;
using namespace ::com::sun::star::datatransfer::dnd;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

class DragSourceListener: public WeakImplHelper<XDragSourceListener>
{
    // this is a window where dropped data are shown as text (only text)
public:
    DragSourceListener( );
    ~DragSourceListener();

    virtual void SAL_CALL disposing( const EventObject& Source )
        throw(RuntimeException);

    virtual void SAL_CALL dragDropEnd( const DragSourceDropEvent& dsde )
        throw(RuntimeException);
    virtual void SAL_CALL dragEnter( const DragSourceDragEvent& dsde )
        throw(RuntimeException);
    virtual void SAL_CALL dragExit( const DragSourceEvent& dse )
        throw(RuntimeException);
    virtual void SAL_CALL dragOver( const DragSourceDragEvent& dsde )
        throw(RuntimeException);
    virtual void SAL_CALL dropActionChanged( const DragSourceDragEvent& dsde )
        throw(RuntimeException);

};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
