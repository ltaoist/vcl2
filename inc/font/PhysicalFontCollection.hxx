/* comment */
#pragma once

#include <sal/config.h>

#include <vcl/dllapi.h>

#include <font/LogicalFontInstance.hxx>

#include "PhysicalFontFamily.hxx"

#include <array>
#include <string_view>

#define MAX_GLYPHFALLBACK 16

namespace vcl::font
{
class GlyphFallbackFontSubstitution;
class PreMatchFontSubstitution;
}

// TODO: merge with ImplFontCache
// TODO: rename to LogicalFontManager

namespace vcl::font
{

class VCL_PLUGIN_PUBLIC PhysicalFontCollection final
{
public:
    explicit                PhysicalFontCollection();
                            ~PhysicalFontCollection();

    // fill the list with device font faces
    void                    Add( vcl::font::PhysicalFontFace* );
    void                    Clear();
    int                     Count() const { return maPhysicalFontFamilies.size(); }

    // find the device font family
    vcl::font::PhysicalFontFamily* FindFontFamily( std::u16string_view rFontName ) const;
    vcl::font::PhysicalFontFamily* FindOrCreateFontFamily( const OUString &rFamilyName );
    vcl::font::PhysicalFontFamily* FindFontFamily( vcl::font::FontSelectPattern& ) const;
    vcl::font::PhysicalFontFamily* FindFontFamilyByTokenNames(std::u16string_view rTokenStr) const;
    vcl::font::PhysicalFontFamily* FindFontFamilyByAttributes(ImplFontAttrs nSearchType, FontWeight, FontWidth,
                                             FontItalic, std::u16string_view rSearchFamily) const;

    // suggest fonts for glyph fallback
    vcl::font::PhysicalFontFamily* GetGlyphFallbackFont( vcl::font::FontSelectPattern&,
                                                  LogicalFontInstance* pLogicalFont,
                                                  OUString& rMissingCodes, int nFallbackLevel ) const;

    // prepare platform specific font substitutions
    void                    SetPreMatchHook( vcl::font::PreMatchFontSubstitution* );
    void                    SetFallbackHook( vcl::font::GlyphFallbackFontSubstitution* );

    // misc utilities
    std::shared_ptr<PhysicalFontCollection> Clone() const;
    std::unique_ptr<vcl::font::PhysicalFontFaceCollection> GetFontFaceCollection() const;

private:
    mutable bool            mbMatchData;    // true if matching attributes are initialized

    typedef std::unordered_map<OUString, std::unique_ptr<vcl::font::PhysicalFontFamily>> PhysicalFontFamilies;
    PhysicalFontFamilies    maPhysicalFontFamilies;

    vcl::font::PreMatchFontSubstitution* mpPreMatchHook;       // device specific prematch substitution
    vcl::font::GlyphFallbackFontSubstitution* mpFallbackHook;  // device specific glyph fallback substitution

    mutable std::unique_ptr<std::array<vcl::font::PhysicalFontFamily*,MAX_GLYPHFALLBACK>> mpFallbackList;
    mutable int             mnFallbackCount;

    void                    ImplInitMatchData() const;
    void                    ImplInitGenericGlyphFallback() const;

    vcl::font::PhysicalFontFamily* ImplFindFontFamilyBySearchName( const OUString& ) const;
    vcl::font::PhysicalFontFamily* ImplFindFontFamilyBySubstFontAttr( const utl::FontNameAttr& ) const;

    vcl::font::PhysicalFontFamily* ImplFindFontFamilyOfDefaultFont() const;

};

}

/* comment */
