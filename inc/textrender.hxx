/* comment */
#pragma once

#include <sal/config.h>

#include "salgdi.hxx"

class ImplFontMetricData;
class PhysicalFontCollection;
namespace vcl::font { class PhysicalFontFace; }

class TextRenderImpl
{
public:
    // can't call ReleaseFonts here, as the destructor just calls this classes SetFont (pure virtual)!
    virtual ~TextRenderImpl() {}

    virtual void                    SetTextColor( Color nColor ) = 0;
    virtual void                    SetFont(LogicalFontInstance*, int nFallbackLevel) = 0;
    void ReleaseFonts() { SetFont(nullptr, 0); }
    virtual void                    GetFontMetric( ImplFontMetricDataRef&, int nFallbackLevel ) = 0;
    virtual FontCharMapRef          GetFontCharMap() const = 0;
    virtual bool                    GetFontCapabilities(vcl::FontCapabilities &rFontCapabilities) const = 0;
    virtual void                    GetDevFontList( vcl::font::PhysicalFontCollection* ) = 0;
    virtual void                    ClearDevFontCache() = 0;
    virtual bool                    AddTempDevFont( vcl::font::PhysicalFontCollection*, const OUString& rFileURL, const OUString& rFontName ) = 0;

    virtual std::unique_ptr<GenericSalLayout>
                                    GetTextLayout(int nFallbackLevel) = 0;
    virtual void                    DrawTextLayout(const GenericSalLayout&, const SalGraphics&) = 0;
};

/* vim:set tabstop=4 shiftwidth=4 softtabstop=4 expandtab: */
