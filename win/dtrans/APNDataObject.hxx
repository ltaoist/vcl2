/* comment */
#pragma once

#if !defined WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <objidl.h>

#include <systools/win32/comtools.hxx>

/*
    an APartment Neutral dataobject wrapper; this wrapper of an IDataObject
    pointer can be used from any apartment without RPC_E_WRONG_THREAD
    which normally occurs if an apartment tries to use an interface
    pointer of another apartment; we use containment to hold the original
    DataObject
*/
class CAPNDataObject : public IDataObject
{
public:
    explicit CAPNDataObject(IDataObjectPtr rIDataObject);
    virtual ~CAPNDataObject();

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
    HRESULT MarshalIDataObjectIntoCurrentApartment( IDataObject** ppIDataObj );

private:
    IDataObjectPtr  m_rIDataObjectOrg;
    HGLOBAL         m_hGlobal;
    LONG            m_nRefCnt;

// prevent copy and assignment
private:
    CAPNDataObject( const CAPNDataObject& theOther );
    CAPNDataObject& operator=( const CAPNDataObject& theOther );
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
