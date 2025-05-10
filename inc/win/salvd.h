/* comment */
#ifndef INCLUDED_VCL_INC_WIN_SALVD_H
#define INCLUDED_VCL_INC_WIN_SALVD_H

#include <sal/config.h>
#include <win/scoped_gdi.hxx>

#include <memory>

#include <salvd.hxx>

class WinSalGraphics;


class WinSalVirtualDevice : public SalVirtualDevice
{
private:
    HDC                     mhLocalDC;              // HDC or 0 for Cache Device
    ScopedHBITMAP           mhBmp;                  // Memory Bitmap
    HBITMAP                 mhDefBmp;               // Default Bitmap
    std::unique_ptr<WinSalGraphics> mpGraphics;     // current VirDev graphics
    WinSalVirtualDevice*    mpNext;                 // next VirDev
    sal_uInt16              mnBitCount;             // BitCount (0 or 1)
    bool                    mbGraphics;             // is Graphics used
    bool                    mbForeignDC;            // uses a foreign DC instead of a bitmap
    tools::Long                    mnWidth;
    tools::Long                    mnHeight;

public:
    HDC getHDC() const { return mhLocalDC; }
    WinSalGraphics* getGraphics() const { return mpGraphics.get(); }
    void setGraphics(WinSalGraphics* pVirGraphics) { mpGraphics.reset(pVirGraphics); }
    WinSalVirtualDevice* getNext() const { return mpNext; }

    WinSalVirtualDevice(HDC hDC = nullptr, HBITMAP hBMP = nullptr, sal_uInt16 nBitCount = 0, bool bForeignDC = false, tools::Long nWidth = 0, tools::Long nHeight = 0);
    virtual ~WinSalVirtualDevice() override;

    virtual SalGraphics*    AcquireGraphics() override;
    virtual void            ReleaseGraphics( SalGraphics* pGraphics ) override;
    virtual bool            SetSize( tools::Long nNewDX, tools::Long nNewDY ) override;

    static HBITMAP ImplCreateVirDevBitmap(HDC hDC, tools::Long nDX, tools::Long nDY, sal_uInt16 nBitCount, void **ppDummy);

    // SalGeometryProvider
    virtual tools::Long GetWidth() const override { return mnWidth; }
    virtual tools::Long GetHeight() const override { return mnHeight; }
};


#endif // INCLUDED_VCL_INC_WIN_SALVD_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
