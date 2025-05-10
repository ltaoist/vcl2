/* comment */
#include <sal/config.h>

#include <string_view>

#include <config_folders.h>

#include <rtl/ustring.hxx>
#include <rtl/bootstrap.hxx>
#include <osl/process.h>
#include <tools/urlobj.hxx>
#include <tools/stream.hxx>
#include <i18nlangtag/languagetag.hxx>
#include <vcl/filter/PngImageReader.hxx>
#include <vcl/bitmapex.hxx>
#include <vcl/svapp.hxx>

namespace {
    bool loadPng( std::u16string_view rPath, BitmapEx &rBitmap)
    {
        INetURLObject aObj( rPath );
        SvFileStream aStrm( aObj.PathToFileName(), StreamMode::STD_READ );
        if ( !aStrm.GetError() ) {
            vcl::PngImageReader aReader( aStrm );
            rBitmap = aReader.read();
            return !rBitmap.IsEmpty();
        }
        else
            return false;
    }
    bool tryLoadPng( std::u16string_view rBaseDir, std::u16string_view rName, BitmapEx& rBitmap )
    {
        return loadPng( rtl::Concat2View(OUString::Concat(rBaseDir) + "/" LIBO_ETC_FOLDER + rName), rBitmap);
    }
}

bool Application::LoadBrandBitmap (std::u16string_view pName, BitmapEx &rBitmap)
{
    // TODO - if we want more flexibility we could add a branding path
    // in an rc file perhaps fallback to "about.bmp"
    OUString aBaseDir( "$BRAND_BASE_DIR");
    rtl::Bootstrap::expandMacros( aBaseDir );
    OUString aBaseName(OUStringChar('/') + pName);
    OUString aPng( ".png" );

    rtl_Locale *pLoc = nullptr;
    osl_getProcessLocale (&pLoc);
    LanguageTag aLanguageTag( *pLoc);

    ::std::vector< OUString > aFallbacks( aLanguageTag.getFallbackStrings( true));
    for (const OUString & aFallback : aFallbacks)
    {
        if (tryLoadPng( aBaseDir, Concat2View(aBaseName + "-" + aFallback + aPng), rBitmap))
            return true;
    }

    return tryLoadPng( aBaseDir, Concat2View(aBaseName + aPng), rBitmap);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
