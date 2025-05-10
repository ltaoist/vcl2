/* comment */
#pragma once

#include <i18nlangtag/lang.h>
#include <tools/degree.hxx>

#include <vcl/vclenum.hxx>

#include <fontattributes.hxx>

#include <ostream>

namespace vcl { class Font; }

class LogicalFontInstance;
class Size;

namespace vcl::font
{
class PhysicalFontFace;

class VCL_DLLPUBLIC FontSelectPattern : public FontAttributes
{
public:
    FontSelectPattern(const vcl::Font&, OUString aSearchName,
                      const Size&, float fExactHeight, bool bNonAntialias = false);
#ifdef _WIN32
                    FontSelectPattern( const PhysicalFontFace&, const Size&,
                                                 float fExactHeight, int nOrientation, bool bVertical );
#endif

    size_t          hashCode() const;
    bool operator==(const FontSelectPattern& rOther) const;
    bool operator!=(const FontSelectPattern& rOther) const
    {
        return !(*this == rOther);
    }

    static const char FEAT_PREFIX;
    static const char FEAT_SEPARATOR;

public:
    OUString        maTargetName;               // name of the font name token that is chosen
    OUString        maSearchName;               // name of the font that matches best
    int             mnWidth;                    // width of font in pixel units
    int             mnHeight;                   // height of font in pixel units
    float           mfExactHeight;              // requested height (in pixels with subpixel details)
    Degree10        mnOrientation;              // text orientation in 1/10 degree (0-3600)
    LanguageType    meLanguage;                 // text language
    bool            mbVertical;                 // vertical mode of requested font
    bool            mbNonAntialiased;           // true if antialiasing is disabled

    bool            mbEmbolden;                 // Force emboldening
    ItalicMatrix    maItalicMatrix;             // Force matrix for slant
};
}

template< typename charT, typename traits >
inline std::basic_ostream<charT, traits> & operator <<(
    std::basic_ostream<charT, traits> & stream, const vcl::font::FontSelectPattern & rFSP)
{
    stream << (rFSP.maTargetName.isEmpty() ? "<default>" : rFSP.maTargetName)
           << " (" << rFSP.maSearchName << ") w: " << rFSP.mnWidth << " h: "
           << rFSP.mnHeight << " alias: " << rFSP.mbNonAntialiased;
    return stream;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
