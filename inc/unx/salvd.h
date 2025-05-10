/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALVD_H
#define INCLUDED_VCL_INC_UNX_SALVD_H

#include <X11/Xlib.h>

#include <unx/saldisp.hxx>
#include <unx/saltype.h>
#include <salvd.hxx>

#include <memory>

class SalDisplay;
class X11SalGraphics;

class X11SalVirtualDevice final : public SalVirtualDevice
{
    SalDisplay      *pDisplay_;
    std::unique_ptr<X11SalGraphics> pGraphics_;

    Pixmap          hDrawable_;
    SalX11Screen    m_nXScreen;

    int             nDX_;
    int             nDY_;
    sal_uInt16      nDepth_;
    bool        bGraphics_;         // is Graphics used
    bool        bExternPixmap_;

public:
    X11SalVirtualDevice(const SalGraphics& rGraphics, tools::Long &nDX, tools::Long &nDY,
            DeviceFormat eFormat, const SystemGraphicsData *pData, std::unique_ptr<X11SalGraphics> pNewGraphics);

    virtual ~X11SalVirtualDevice() override;

    Display *GetXDisplay() const
    {
        return pDisplay_->GetDisplay();
    }
    SalDisplay *GetDisplay() const
    {
        return pDisplay_;
    }
    Pixmap          GetDrawable() const { return hDrawable_; }
    sal_uInt16      GetDepth() const { return nDepth_; }
    const SalX11Screen&     GetXScreenNumber() const { return m_nXScreen; }

    virtual SalGraphics*    AcquireGraphics() override;
    virtual void            ReleaseGraphics( SalGraphics* pGraphics ) override;

    /// Set new size, without saving the old contents
    virtual bool        SetSize( tools::Long nNewDX, tools::Long nNewDY ) override;

    // SalGeometryProvider
    virtual tools::Long GetWidth() const override { return nDX_; }
    virtual tools::Long GetHeight() const override { return nDY_; }
};

#endif // INCLUDED_VCL_INC_UNX_SALVD_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
