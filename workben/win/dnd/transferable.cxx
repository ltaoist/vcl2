/* comment */
#include "transferable.hxx"

//  ctor

CTransferable::CTransferable( wchar_t* dataString ) :
    m_seqDFlv( 1 ),
    m_Data( dataString )
{
    DataFlavor df;

    /*
    df.MimeType = L"text/plain; charset=unicode";
    df.DataType = cppu::UnoType<OUString>::get();

    m_seqDFlv[0] = df;
    */

    //df.MimeType = L"text/plain; charset=windows1252";
    df.MimeType = L"text/plain";
    df.DataType = cppu::UnoType<Sequence< sal_Int8 >>::get();

    m_seqDFlv[0] = df;
}

//  getTransferData

Any SAL_CALL CTransferable::getTransferData( const DataFlavor& aFlavor )
    throw(UnsupportedFlavorException, IOException, RuntimeException)
{
    Any anyData;

    /*if ( aFlavor == m_seqDFlv[0] )
    {
        anyData = makeAny( m_Data );
    }
    else*/ if ( aFlavor == m_seqDFlv[0] )
    {
        OString aStr( m_Data.getStr( ), m_Data.getLength( ), 1252 );
        Sequence< sal_Int8 > sOfChars( aStr.getLength( ) );
        sal_Int32 lenStr = aStr.getLength( );

        for ( sal_Int32 i = 0; i < lenStr; ++i )
            sOfChars[i] = aStr[i];

        anyData = makeAny( sOfChars );
    }

    return anyData;
}

//  getTransferDataFlavors

Sequence< DataFlavor > SAL_CALL CTransferable::getTransferDataFlavors(  )
    throw(RuntimeException)
{
    return m_seqDFlv;
}

//  isDataFlavorSupported

sal_Bool SAL_CALL CTransferable::isDataFlavorSupported( const DataFlavor& aFlavor )
    throw(RuntimeException)
{
    sal_Int32 nLength = m_seqDFlv.getLength( );
    sal_Bool bRet     = sal_False;

    for ( sal_Int32 i = 0; i < nLength; ++i )
    {
        if ( m_seqDFlv[i] == aFlavor )
        {
            bRet = sal_True;
            break;
        }
    }

    return bRet;
}

//  lostOwnership

void SAL_CALL CTransferable::lostOwnership( const Reference< XClipboard >& xClipboard, const Reference< XTransferable >& xTrans )
    throw(RuntimeException)
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
