/* comment */
#ifndef INCLUDED_VCL_INC_QUARTZ_SALVD_H
#define INCLUDED_VCL_INC_QUARTZ_SALVD_H

#include <premac.h>
#ifdef MACOSX
#include <ApplicationServices/ApplicationServices.h>
#else
#include <CoreGraphics/CoreGraphics.h>
#endif
#include <postmac.h>

#include <tools/long.hxx>

#include <quartz/salgdi.h>

#include <salvd.hxx>

class AquaSalGraphics;

class AquaSalVirtualDevice : public SalVirtualDevice
{
private:
    bool mbGraphicsUsed;             // is Graphics used
    bool mbForeignContext;           // is mxContext from outside VCL
    CGContextHolder maBitmapContext;
    int mnBitmapDepth;
    CGLayerHolder maLayer;
    AquaSalGraphics* mpGraphics;     // current VirDev graphics

    tools::Long mnWidth;
    tools::Long mnHeight;

    void Destroy();

public:
    AquaSalVirtualDevice( AquaSalGraphics* pGraphic, tools::Long &nDX, tools::Long &nDY, DeviceFormat eFormat, const SystemGraphicsData *pData );
    virtual ~AquaSalVirtualDevice() override;

    virtual SalGraphics*            AcquireGraphics() override;
    virtual void                    ReleaseGraphics( SalGraphics* pGraphics ) override;
    virtual bool                    SetSize( tools::Long nNewDX, tools::Long nNewDY ) override;

    tools::Long GetWidth() const override
    {
        return mnWidth;
    }

    tools::Long GetHeight() const override
    {
        return mnHeight;
    }
};

#endif // INCLUDED_VCL_INC_QUARTZ_SALVD_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
