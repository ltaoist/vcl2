/* comment */
#pragma once

#include <sal/config.h>

#include <rtl/ustring.hxx>

#include <sallayout.hxx>
#include <svsys.h>
#include <win/salgdi.h>
#include <o3tl/sorted_vector.hxx>

// win32 specific logical font instance
class WinFontInstance : public LogicalFontInstance
{
    friend rtl::Reference<LogicalFontInstance> WinFontFace::CreateFontInstance(const vcl::font::FontSelectPattern&) const;

public:
    ~WinFontInstance() override;

    bool hasHScale() const;
    float getHScale() const;

    void SetGraphics(WinSalGraphics*);
    WinSalGraphics* GetGraphics() const { return m_pGraphics; }

    HFONT GetHFONT() const { return m_hFont; }
    float GetScale() const { return m_fScale; }
    // Return true if the font is for vertical writing.
    // I.e. the font name of the LOGFONT is prefixed with '@'.
    bool  IsCJKVerticalFont() const { return m_bIsCJKVerticalFont; }
    sal_Int32 GetTmDescent() const { return m_nTmDescent; }

    const WinFontFace * GetFontFace() const { return static_cast<const WinFontFace *>(LogicalFontInstance::GetFontFace()); }
    WinFontFace * GetFontFace() { return static_cast<WinFontFace *>(LogicalFontInstance::GetFontFace()); }

    bool GetGlyphOutline(sal_GlyphId, basegfx::B2DPolyPolygon&, bool) const override;

private:
    explicit WinFontInstance(const WinFontFace&, const vcl::font::FontSelectPattern&);

    virtual void ImplInitHbFont(hb_font_t*) override;
    bool ImplGetGlyphBoundRect(sal_GlyphId, tools::Rectangle&, bool) const override;

    WinSalGraphics *m_pGraphics;
    HFONT m_hFont;
    float m_fScale;
    bool  m_bIsCJKVerticalFont;
    sal_Int32 m_nTmDescent;
};

class TextOutRenderer
{
protected:
    explicit TextOutRenderer() = default;
    TextOutRenderer(const TextOutRenderer &) = delete;
    TextOutRenderer & operator = (const TextOutRenderer &) = delete;

public:
    static TextOutRenderer & get(bool bUseDWrite, bool bRenderingModeNatural);

    virtual ~TextOutRenderer() = default;

    virtual bool operator ()(GenericSalLayout const &rLayout,
        SalGraphics &rGraphics,
        HDC hDC,
        bool bRenderingModeNatural) = 0;
};

class ExTextOutRenderer : public TextOutRenderer
{
    ExTextOutRenderer(const ExTextOutRenderer &) = delete;
    ExTextOutRenderer & operator = (const ExTextOutRenderer &) = delete;

public:
    explicit ExTextOutRenderer() = default;

    bool operator ()(GenericSalLayout const &rLayout,
        SalGraphics &rGraphics,
        HDC hDC,
        bool bRenderingModeNatural) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
