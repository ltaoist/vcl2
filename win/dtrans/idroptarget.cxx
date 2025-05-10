/* comment */
#include "idroptarget.hxx"

IDropTargetImpl::IDropTargetImpl( DropTarget& pTarget): m_nRefCount( 0),
                                    m_rDropTarget( pTarget)
{
}

IDropTargetImpl::~IDropTargetImpl()
{
}

//IDropTarget
HRESULT STDMETHODCALLTYPE IDropTargetImpl::QueryInterface( REFIID riid, void  **ppvObject)
{
    if( !ppvObject)
        return E_POINTER;
    *ppvObject= nullptr;

    if( riid == __uuidof( IUnknown))
        *ppvObject= static_cast<IUnknown*>( this);
    else if (  riid == __uuidof( IDropTarget))
        *ppvObject= static_cast<IDropTarget*>( this);

    if(*ppvObject)
    {
        AddRef();
        return S_OK;
    }
    else
        return E_NOINTERFACE;

}

ULONG STDMETHODCALLTYPE IDropTargetImpl::AddRef()
{
    return InterlockedIncrement( &m_nRefCount);
}

ULONG STDMETHODCALLTYPE IDropTargetImpl::Release()
{
    LONG count= InterlockedDecrement( &m_nRefCount);
    if( m_nRefCount == 0 )
        delete this;
    return count;
}

STDMETHODIMP IDropTargetImpl::DragEnter( IDataObject __RPC_FAR *pDataObj,
                                    DWORD grfKeyState,
                                    POINTL pt,
                                    DWORD  *pdwEffect)
{
    return m_rDropTarget.DragEnter( pDataObj, grfKeyState,
                                  pt, pdwEffect);
}

STDMETHODIMP IDropTargetImpl::DragOver( DWORD grfKeyState,
                                   POINTL pt,
                                   DWORD  *pdwEffect)
{
    return m_rDropTarget.DragOver( grfKeyState, pt, pdwEffect);
}

STDMETHODIMP IDropTargetImpl::DragLeave()
{
    return m_rDropTarget.DragLeave();
}

STDMETHODIMP IDropTargetImpl::Drop( IDataObject  *pDataObj,
                   DWORD grfKeyState,
                   POINTL pt,
                   DWORD __RPC_FAR *pdwEffect)
{
    return m_rDropTarget.Drop( pDataObj, grfKeyState,
                                   pt, pdwEffect);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
