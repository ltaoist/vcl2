/* comment */
#pragma once

#include <headless/svpvd.hxx>
#include <QtSvpGraphics.hxx>

class VCL_DLLPUBLIC QtSvpVirtualDevice : public SvpSalVirtualDevice
{
public:
    QtSvpVirtualDevice(cairo_surface_t* pRefSurface, cairo_surface_t* pPreExistingTarget)
        : SvpSalVirtualDevice(pRefSurface, pPreExistingTarget)
    {
    }

    SalGraphics* AcquireGraphics() override { return AddGraphics(new QtSvpGraphics(nullptr)); }
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
