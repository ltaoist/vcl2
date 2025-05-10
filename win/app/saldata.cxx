/* comment */
#include <svsys.h>
#include <rtl/tencinfo.h>
#include <vcl/svapp.hxx>

#include <win/saldata.hxx>

rtl_TextEncoding ImplSalGetSystemEncoding()
{
    static const UINT nOldAnsiCodePage = 0;
    static rtl_TextEncoding eEncoding = RTL_TEXTENCODING_MS_1252;

    UINT nAnsiCodePage = GetACP();
    if ( nAnsiCodePage != nOldAnsiCodePage )
    {
        rtl_TextEncoding nEnc
            = rtl_getTextEncodingFromWindowsCodePage(nAnsiCodePage);
        if (nEnc != RTL_TEXTENCODING_DONTKNOW)
            eEncoding = nEnc;
    }

    return eEncoding;
}

OUString ImplSalGetUniString(const char* pStr, sal_Int32 const nLen)
{
    return OUString( pStr, (-1 == nLen) ? strlen(pStr) : nLen,
                      ImplSalGetSystemEncoding(),
                      RTL_TEXTTOUNICODE_FLAGS_UNDEFINED_DEFAULT |
                      RTL_TEXTTOUNICODE_FLAGS_MBUNDEFINED_DEFAULT |
                      RTL_TEXTTOUNICODE_FLAGS_INVALID_DEFAULT );
}

int ImplSalWICompareAscii( const wchar_t* pStr1, const char* pStr2 )
{
    int         nRet;
    char       c2;
    do
    {
        // change to LowerCase if the char is between 'A' and 'Z'
        wchar_t c1 = *pStr1;
        c2 = *pStr2;
        if ( (c1 >= 65) && (c1 <= 90) )
            c1 += 32;
        if ( (c2 >= 65) && (c2 <= 90) )
            c2 += 32;
        nRet = static_cast<sal_Int32>(c1)- static_cast<sal_Int32>(static_cast<unsigned char>(c2));
        if ( nRet != 0 )
            break;

        pStr1++;
        pStr2++;
    }
    while ( c2 );

    return nRet;
}


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
