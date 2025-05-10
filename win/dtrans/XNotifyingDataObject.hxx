/* comment */
#pragma once

#include <com/sun/star/datatransfer/XTransferable.hpp>
#include <com/sun/star/datatransfer/clipboard/XClipboardOwner.hpp>

#if !defined WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <objidl.h>

#include <systools/win32/comtools.hxx>

/*--------------------------------------------------------------------------
    To implement the lostOwnership mechanism cleanly we need this wrapper
    object
----------------------------------------------------------------------------*/

// forward
class CWinClipboard;

class CXNotifyingDataObject final : public IDataObject
{
public:
    CXNotifyingDataObject(
        const IDataObjectPtr& aIDataObject,
        const css::uno::Reference< css::datatransfer::XTransferable >& aXTransferable,
        const css::uno::Reference< css::datatransfer::clipboard::XClipboardOwner >& aXClipOwner,
        CWinClipboard* const theWinClipoard);

    virtual ~CXNotifyingDataObject() {}

    // ole interface implementation

    //IUnknown interface methods
    STDMETHODIMP           QueryInterface(REFIID iid, void** ppvObject) override;
    STDMETHODIMP_( ULONG ) AddRef( ) override;
    STDMETHODIMP_( ULONG ) Release( ) override;

    // IDataObject interface methods
    STDMETHODIMP GetData( FORMATETC * pFormatetc, STGMEDIUM * pmedium ) override;
    STDMETHODIMP GetDataHere( FORMATETC * pFormatetc, STGMEDIUM * pmedium ) override;
    STDMETHODIMP QueryGetData( FORMATETC * pFormatetc ) override;
    STDMETHODIMP GetCanonicalFormatEtc( FORMATETC * pFormatectIn, FORMATETC * pFormatetcOut ) override;
    STDMETHODIMP SetData( FORMATETC * pFormatetc, STGMEDIUM * pmedium, BOOL fRelease ) override;
    STDMETHODIMP EnumFormatEtc( DWORD dwDirection, IEnumFORMATETC** ppenumFormatetc ) override;
    STDMETHODIMP DAdvise( FORMATETC * pFormatetc, DWORD advf, IAdviseSink * pAdvSink, DWORD* pdwConnection ) override;
    STDMETHODIMP DUnadvise( DWORD dwConnection ) override;
    STDMETHODIMP EnumDAdvise( IEnumSTATDATA** ppenumAdvise ) override;

    operator IDataObject*( );

private:
    void lostOwnership( );

    sal_Int32                                                                     m_nRefCnt;
    IDataObjectPtr                                                                m_aIDataObject;
    const css::uno::Reference< css::datatransfer::XTransferable >                 m_XTransferable;
    const css::uno::Reference< css::datatransfer::clipboard::XClipboardOwner >    m_XClipboardOwner;
    CWinClipboard* const m_pWinClipImpl;

    friend class CWinClipboard;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
