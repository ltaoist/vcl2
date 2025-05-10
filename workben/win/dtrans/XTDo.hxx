/* comment */
#pragma once

#if defined _MSC_VER
#pragma warning(push,1)
#endif
#include <windows.h>
#include <ole2.h>
#include <objidl.h>
#if defined _MSC_VER
#pragma warning(pop)
#endif

#include <vector>

class EnumFormatEtc;

/*--------------------------------------------------------------------------
    - the function principle of the windows clipboard:
      a data provider offers all formats he can deliver on the clipboard
      a clipboard client ask for the available formats on the clipboard
      and decides if there is a format he can use
      if there is one, he requests the data in this format

    - This class inherits from IDataObject and so can be placed on the
      OleClipboard. The class wraps a transferable object which is the
      original DataSource
    - DataFlavors offered by this transferable will be translated into
      appropriate clipboard formats
    - if the transferable contains text data always text and unicodetext
      will be offered or vice versa
    - text data will be automatically converted between text and unicode text
    - although the transferable may support text in different charsets
      (codepages) only text in one codepage can be offered by the clipboard

----------------------------------------------------------------------------*/

class CXTDataObject : public IDataObject
{
public:
    CXTDataObject( );

    // ole interface implementation

    //IUnknown interface methods
    STDMETHODIMP           QueryInterface(REFIID iid, LPVOID* ppvObject);
    STDMETHODIMP_( ULONG ) AddRef( );
    STDMETHODIMP_( ULONG ) Release( );

    // IDataObject interface methods
    STDMETHODIMP GetData( LPFORMATETC pFormatetc, LPSTGMEDIUM pmedium );
    STDMETHODIMP GetDataHere( LPFORMATETC pFormatetc, LPSTGMEDIUM pmedium );
    STDMETHODIMP QueryGetData( LPFORMATETC pFormatetc );
    STDMETHODIMP GetCanonicalFormatEtc( LPFORMATETC pFormatectIn, LPFORMATETC pFormatetcOut );
    STDMETHODIMP SetData( LPFORMATETC pFormatetc, LPSTGMEDIUM pmedium, BOOL fRelease );
    STDMETHODIMP EnumFormatEtc( DWORD dwDirection, IEnumFORMATETC** ppenumFormatetc );
    STDMETHODIMP DAdvise( LPFORMATETC pFormatetc, DWORD advf, LPADVISESINK pAdvSink, DWORD* pdwConnection );
    STDMETHODIMP DUnadvise( DWORD dwConnection );
    STDMETHODIMP EnumDAdvise( LPENUMSTATDATA* ppenumAdvise );

    operator IDataObject*( );

private:

private:
    LONG m_nRefCnt;
};

class CEnumFormatEtc : public IEnumFORMATETC
{
public:
    explicit CEnumFormatEtc( LPUNKNOWN pUnkDataObj );

    // IUnknown
    STDMETHODIMP           QueryInterface( REFIID iid, LPVOID* ppvObject );
    STDMETHODIMP_( ULONG ) AddRef( );
    STDMETHODIMP_( ULONG ) Release( );

    //IEnumFORMATETC
    STDMETHODIMP Next( ULONG celt, LPFORMATETC rgelt, ULONG* pceltFetched );
    STDMETHODIMP Skip( ULONG celt );
    STDMETHODIMP Reset( );
    STDMETHODIMP Clone( IEnumFORMATETC** ppenum );

private:
    LONG                                m_nRefCnt;
    LPUNKNOWN                           m_pUnkDataObj;
    ULONG                               m_nCurrPos;
};

typedef CEnumFormatEtc *PCEnumFormatEtc;

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
