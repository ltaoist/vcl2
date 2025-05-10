/* comment */
#ifndef INCLUDED_VCL_UNX_GENERIC_GDI_X11CAIROTEXTRENDER_HXX
#define INCLUDED_VCL_UNX_GENERIC_GDI_X11CAIROTEXTRENDER_HXX

#include <unx/cairotextrender.hxx>
#include <unx/salgdi.h>

class X11CairoTextRender final : public CairoTextRender
{
    X11SalGraphics& mrParent;

public:
    explicit X11CairoTextRender(X11SalGraphics& rParent);

    virtual cairo_t* getCairoContext() override;
    virtual void getSurfaceOffset(double& nDX, double& nDY) override;
    virtual void clipRegion(cairo_t* cr) override;
    virtual void releaseCairoContext(cairo_t* cr) override;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
