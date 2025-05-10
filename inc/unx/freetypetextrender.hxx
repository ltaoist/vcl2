/* comment */
#pragma once

#include <sal/config.h>

#include <textrender.hxx>

class FreetypeFontInstance;

// Generic implementation that uses freetype, but DrawTextLayout()
// still needs implementing (e.g. by Cairo or Skia).
class VCL_DLLPUBLIC FreeTypeTextRenderImpl : public TextRenderImpl
{
protected:
    rtl::Reference<FreetypeFontInstance>
                            mpFreetypeFont[ MAX_FALLBACK ];

    Color           mnTextColor;

public:
    FreeTypeTextRenderImpl();
    virtual ~FreeTypeTextRenderImpl() override;

    virtual void                SetTextColor( Color nColor ) override;
    virtual void                SetFont(LogicalFontInstance*, int nFallbackLevel) override;
    virtual void                GetFontMetric( ImplFontMetricDataRef&, int nFallbackLevel ) override;
    virtual FontCharMapRef      GetFontCharMap() const override;
    virtual bool                GetFontCapabilities(vcl::FontCapabilities &rFontCapabilities) const override;
    virtual void                GetDevFontList( vcl::font::PhysicalFontCollection* ) override;
    virtual void                ClearDevFontCache() override;
    virtual bool                AddTempDevFont( vcl::font::PhysicalFontCollection*, const OUString& rFileURL, const OUString& rFontName ) override;

    virtual std::unique_ptr<GenericSalLayout>
                                GetTextLayout(int nFallbackLevel) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
