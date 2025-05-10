/* comment */
#pragma once

#include <sal/config.h>

#include <font/PhysicalFontFace.hxx>
#include <font/LogicalFontInstance.hxx>

namespace vcl::pdf
{
struct BuildinFont
{
    const char* m_pName;
    const char* m_pStyleName;
    const char* m_pPSName;
    int const m_nAscent;
    int const m_nDescent;
    FontFamily const m_eFamily;
    rtl_TextEncoding const m_eCharSet;
    FontPitch const m_ePitch;
    FontWidth const m_eWidthType;
    FontWeight const m_eWeight;
    FontItalic const m_eItalic;
    int const m_aWidths[256];
    mutable FontCharMapRef m_xFontCharMap;

    OString getNameObject() const;
    const FontCharMapRef& GetFontCharMap() const;
    FontAttributes GetFontAttributes() const;
};

class BuildinFontInstance final : public LogicalFontInstance
{
    bool ImplGetGlyphBoundRect(sal_GlyphId nID, tools::Rectangle& rRect, bool) const override;

public:
    BuildinFontInstance(const vcl::font::PhysicalFontFace&, const vcl::font::FontSelectPattern&);

    bool GetGlyphOutline(sal_GlyphId nId, basegfx::B2DPolyPolygon& rPoly, bool) const override;
};

class BuildinFontFace final : public vcl::font::PhysicalFontFace
{
    static const BuildinFont m_aBuildinFonts[14];
    const BuildinFont& mrBuildin;

    rtl::Reference<LogicalFontInstance>
    CreateFontInstance(const vcl::font::FontSelectPattern& rFSD) const override;

public:
    explicit BuildinFontFace(int nId);

    const BuildinFont& GetBuildinFont() const { return mrBuildin; }
    sal_IntPtr GetFontId() const override { return reinterpret_cast<sal_IntPtr>(&mrBuildin); }
    FontCharMapRef GetFontCharMap() const override { return mrBuildin.GetFontCharMap(); }
    bool GetFontCapabilities(vcl::FontCapabilities&) const override { return false; }

    static const BuildinFont& Get(int nId) { return m_aBuildinFonts[nId]; }
};

} // namespace vcl::pdf

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
