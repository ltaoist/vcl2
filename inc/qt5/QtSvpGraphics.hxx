/* comment */
#pragma once

#include <vclpluginapi.h>
#include <headless/svpgdi.hxx>

#include "QtGraphicsBase.hxx"

class QtFrame;

class VCLPLUG_QT_PUBLIC QtSvpGraphics final : public SvpSalGraphics, public QtGraphicsBase
{
    QtFrame* const m_pFrame;

    void handleDamage(const tools::Rectangle&) override;

public:
    QtSvpGraphics(QtFrame* pFrame);
    ~QtSvpGraphics() override;

    void updateQWidget() const;

#if ENABLE_CAIRO_CANVAS
    bool SupportsCairo() const override;
    cairo::SurfaceSharedPtr
    CreateSurface(const cairo::CairoSurfaceSharedPtr& rSurface) const override;
    cairo::SurfaceSharedPtr CreateSurface(const OutputDevice& rRefDevice, int x, int y, int width,
                                          int height) const override;
#endif // ENABLE_CAIRO_CANVAS

    virtual void GetResolution(sal_Int32& rDPIX, sal_Int32& rDPIY) override;

    virtual OUString getRenderBackendName() const override { return "qt5svp"; }
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
