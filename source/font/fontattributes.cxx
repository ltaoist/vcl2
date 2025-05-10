/* comment */
#include <fontattributes.hxx>

FontAttributes::FontAttributes()
:   meWeight( WEIGHT_DONTKNOW ),
    meFamily( FAMILY_DONTKNOW ),
    mePitch( PITCH_DONTKNOW ),
    meWidthType ( WIDTH_DONTKNOW ),
    meItalic ( ITALIC_NONE ),
    meCharSet( RTL_TEXTENCODING_DONTKNOW ),
    mbSymbolFlag( false ),
    mnQuality( 0 )
{}

bool FontAttributes::CompareDeviceIndependentFontAttributes(const FontAttributes& rOther) const
{
    if (maFamilyName != rOther.maFamilyName)
        return false;

    if (maStyleName != rOther.maStyleName)
        return false;

    if (meWeight != rOther.meWeight)
        return false;

    if (meItalic != rOther.meItalic)
        return false;

    if (meFamily != rOther.meFamily)
        return false;

    if (mePitch != rOther.mePitch)
        return false;

    if (meWidthType != rOther.meWidthType)
        return false;

    if (mbSymbolFlag != rOther.mbSymbolFlag)
        return false;

    return true;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
