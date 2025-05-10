/* comment */

#pragma once

#include <sal/config.h>

#include <vcl/cairo.hxx>

class QtSvpGraphics;
class OutputDevice;

namespace cairo
{
class QtSvpSurface final : public Surface
{
    const QtSvpGraphics* m_pGraphics;
    cairo_t* const m_pCairoContext;
    CairoSurfaceSharedPtr m_pSurface;

public:
    /// takes over ownership of passed cairo_surface
    explicit QtSvpSurface(CairoSurfaceSharedPtr pSurface);
    /// create surface on subarea of given drawable
    explicit QtSvpSurface(const QtSvpGraphics* pGraphics, int x, int y, int width, int height);
    ~QtSvpSurface() override;

    // Surface interface
    CairoSharedPtr getCairo() const override;
    CairoSurfaceSharedPtr getCairoSurface() const override { return m_pSurface; }
    SurfaceSharedPtr getSimilar(int nContentType, int width, int height) const override;

    VclPtr<VirtualDevice> createVirtualDevice() const override;
    void flush() const override;
};
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
