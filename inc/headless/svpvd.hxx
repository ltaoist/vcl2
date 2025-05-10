/* comment */
#ifndef INCLUDED_VCL_INC_HEADLESS_SVPVD_HXX
#define INCLUDED_VCL_INC_HEADLESS_SVPVD_HXX

#include <salvd.hxx>
#include <vcl/salgtype.hxx>
#include <basegfx/vector/b2ivector.hxx>

#include <vector>

class SvpSalGraphics;
typedef struct _cairo_surface cairo_surface_t;

class VCL_DLLPUBLIC SvpSalVirtualDevice : public SalVirtualDevice
{
    cairo_surface_t*                    m_pRefSurface;
    cairo_surface_t*                    m_pSurface;
    bool                                m_bOwnsSurface; // nearly always true, except for edge case of tdf#127529
    basegfx::B2IVector                  m_aFrameSize;
    std::vector< SvpSalGraphics* >      m_aGraphics;

    bool CreateSurface(tools::Long nNewDX, tools::Long nNewDY, sal_uInt8 *const pBuffer);

protected:
    SvpSalGraphics* AddGraphics(SvpSalGraphics* aGraphics);

public:
    SvpSalVirtualDevice(cairo_surface_t* pRefSurface, cairo_surface_t* pPreExistingTarget);
    virtual ~SvpSalVirtualDevice() override;

    // SalVirtualDevice
    virtual SalGraphics*    AcquireGraphics() override;
    virtual void            ReleaseGraphics( SalGraphics* pGraphics ) override;

    virtual bool        SetSize( tools::Long nNewDX, tools::Long nNewDY ) override;
    virtual bool        SetSizeUsingBuffer( tools::Long nNewDX, tools::Long nNewDY,
                                            sal_uInt8 * pBuffer
                                          ) override;

    cairo_surface_t* GetSurface() const { return m_pSurface; }

    // SalGeometryProvider
    virtual tools::Long GetWidth() const override;
    virtual tools::Long GetHeight() const override;
};

#endif // INCLUDED_VCL_INC_HEADLESS_SVPVD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
