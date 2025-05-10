/* comment */
#ifndef INCLUDED_VCL_INC_UNX_CAIROTEXTRENDER_HXX
#define INCLUDED_VCL_INC_UNX_CAIROTEXTRENDER_HXX

#include <unx/freetypetextrender.hxx>

class GenericSalLayout;
class SalGraphics;
typedef struct _cairo cairo_t;
typedef struct _cairo_font_options cairo_font_options_t;

class VCL_DLLPUBLIC CairoTextRender : public FreeTypeTextRenderImpl
{
private:
    // https://gitlab.freedesktop.org/cairo/cairo/-/merge_requests/235
    // I don't want to have CAIRO_ROUND_GLYPH_POS_ON set in the cairo
    // surfaces font_options, but that's private, so tricky to achieve
    cairo_font_options_t*       mpRoundGlyphPosOffOptions;
protected:
    virtual cairo_t*            getCairoContext() = 0;
    virtual void                getSurfaceOffset(double& nDX, double& nDY) = 0;
    virtual void                releaseCairoContext(cairo_t* cr) = 0;

    virtual void                clipRegion(cairo_t* cr) = 0;

public:
    virtual void                DrawTextLayout(const GenericSalLayout&, const SalGraphics&) override;
    CairoTextRender();
    virtual ~CairoTextRender();
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
