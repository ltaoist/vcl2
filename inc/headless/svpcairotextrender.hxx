/* comment */

#ifndef INCLUDED_VCL_UNX_GTK3_GDI_GTK3CAIROTEXTRENDER_HXX
#define INCLUDED_VCL_UNX_GTK3_GDI_GTK3CAIROTEXTRENDER_HXX

#include <unx/cairotextrender.hxx>

class SvpSalGraphics;

class SvpCairoTextRender final : public CairoTextRender
{
    SvpSalGraphics& mrParent;

public:
    explicit SvpCairoTextRender(SvpSalGraphics& rParent);

    virtual cairo_t* getCairoContext() override;
    virtual void getSurfaceOffset(double& nDX, double& nDY) override;
    virtual void clipRegion(cairo_t* cr) override;
    virtual void releaseCairoContext(cairo_t* cr) override;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
