/* comment */

#pragma once

#include <sal/config.h>

#include <font/FontSelectPattern.hxx>
#include <font/PhysicalFontFace.hxx>
#include <font/PhysicalFontFaceCollection.hxx>
#include <fontattributes.hxx>
#include <font/LogicalFontInstance.hxx>

class TestFontInstance : public LogicalFontInstance
{
public:
    TestFontInstance(vcl::font::PhysicalFontFace const& rFontFace,
                     vcl::font::FontSelectPattern const& rFontSelectPattern)
        : LogicalFontInstance(rFontFace, rFontSelectPattern)
    {
    }

    bool GetGlyphOutline(sal_GlyphId, basegfx::B2DPolyPolygon&, bool) const override
    {
        return true;
    }

protected:
    bool ImplGetGlyphBoundRect(sal_GlyphId, tools::Rectangle&, bool) const override { return true; }
};

class TestFontFace : public vcl::font::PhysicalFontFace
{
public:
    TestFontFace(sal_uIntPtr nId)
        : vcl::font::PhysicalFontFace(FontAttributes())
        , mnFontId(nId)
    {
    }

    TestFontFace(FontAttributes const& rFontAttributes, sal_uIntPtr nId)
        : vcl::font::PhysicalFontFace(rFontAttributes)
        , mnFontId(nId)
    {
    }

    rtl::Reference<LogicalFontInstance>
    CreateFontInstance(vcl::font::FontSelectPattern const& rFontSelectPattern) const override
    {
        return new TestFontInstance(*this, rFontSelectPattern);
    }

    sal_IntPtr GetFontId() const override { return mnFontId; }
    FontCharMapRef GetFontCharMap() const override { return FontCharMap::GetDefaultMap(false); }
    bool GetFontCapabilities(vcl::FontCapabilities&) const override { return true; }

private:
    sal_IntPtr mnFontId;
};

/* comment */
