/* comment */
#ifndef INCLUDED_VCL_INC_SALVD_HXX
#define INCLUDED_VCL_INC_SALVD_HXX

#include "salgeom.hxx"

class SalGraphics;

/// A non-visible drawable/buffer (e.g. an X11 Pixmap).
class VCL_PLUGIN_PUBLIC SalVirtualDevice
        : public SalGeometryProvider
{
public:
    SalVirtualDevice() {}
    virtual ~SalVirtualDevice() override;

    // SalGeometryProvider
    virtual bool IsOffScreen() const override { return true; }

    // SalGraphics or NULL, but two Graphics for all SalVirtualDevices
    // must be returned
    virtual SalGraphics*    AcquireGraphics() = 0;
    virtual void            ReleaseGraphics( SalGraphics* pGraphics ) = 0;

    // Set new size, without saving the old contents
    virtual bool            SetSize( tools::Long nNewDX, tools::Long nNewDY ) = 0;

    // Set new size using a buffer at the given address
    virtual bool            SetSizeUsingBuffer( tools::Long nNewDX, tools::Long nNewDY,
                                                sal_uInt8 * /* pBuffer */)
        {
            // Only the headless virtual device has an implementation that uses
            // pBuffer (and bTopDown).
            return SetSize( nNewDX, nNewDY );
        }
};

#endif // INCLUDED_VCL_INC_SALVD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
