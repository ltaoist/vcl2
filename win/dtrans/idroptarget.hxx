/* comment */#pragma once

#include <win/dnd_target.hxx>

class IDropTargetImpl: public IDropTarget
{
    LONG m_nRefCount;
    // Calls to IDropTarget functions are delegated to a DropTarget.
    DropTarget& m_rDropTarget;

    virtual ~IDropTargetImpl(); // delete is only called by IUnknown::Release
    IDropTargetImpl( const IDropTargetImpl& );
    IDropTargetImpl& operator=( const IDropTargetImpl& );
public:
    explicit IDropTargetImpl(DropTarget& rTarget);

       // IDropTarget
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) override;

    virtual ULONG STDMETHODCALLTYPE AddRef( ) override;

    virtual ULONG STDMETHODCALLTYPE Release( ) override;

    virtual HRESULT STDMETHODCALLTYPE DragEnter(
            /* [unique][in] */ IDataObject __RPC_FAR *pDataObj,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD __RPC_FAR *pdwEffect) override;

    virtual HRESULT STDMETHODCALLTYPE DragOver(
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD __RPC_FAR *pdwEffect) override;

    virtual HRESULT STDMETHODCALLTYPE DragLeave( ) override;

    virtual HRESULT STDMETHODCALLTYPE Drop(
            /* [unique][in] */ IDataObject __RPC_FAR *pDataObj,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD __RPC_FAR *pdwEffect) override;

};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
