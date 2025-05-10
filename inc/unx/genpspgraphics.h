/* comment */
#pragma once

#include <sal/config.h>

#include <vcl/vclenum.hxx>
#include <config_cairo_canvas.h>

#include <unx/fontmanager.hxx>
#include <salgdi.hxx>
#include <sallayout.hxx>

#include <unx/GenPspGfxBackend.hxx>

namespace vcl::font
{
class PhysicalFontFace;
class PhysicalFontCollection;
}

namespace psp { struct JobData; class PrinterGfx; }

class FreetypeFontInstance;
class FontAttributes;
class SalInfoPrinter;
class ImplFontMetricData;

class VCL_DLLPUBLIC GenPspGraphics final : public SalGraphicsAutoDelegateToImpl
{
    std::unique_ptr<GenPspGfxBackend> m_pBackend;

    psp::JobData*           m_pJobData;
    psp::PrinterGfx*        m_pPrinterGfx;

    rtl::Reference<FreetypeFontInstance>
                            m_pFreetypeFont[ MAX_FALLBACK ];

public:
                            GenPspGraphics();
    virtual                ~GenPspGraphics() override;

    void                    Init( psp::JobData* pJob, psp::PrinterGfx* pGfx );

    // helper methods
    static FontAttributes   Info2FontAttributes(const psp::FastPrintFontInfo&);

    // helper methods for sharing with FreeTypeTextRenderImpl
    static void             GetDevFontListHelper(vcl::font::PhysicalFontCollection*);
    static bool             AddTempDevFontHelper(vcl::font::PhysicalFontCollection* pFontCollection,
                                                 std::u16string_view rFileURL,
                                                 const OUString& rFontName);

    // override all pure virtual methods
    virtual SalGraphicsImpl* GetImpl() const override
    {
        return m_pBackend.get();
    }

    virtual void            GetResolution( sal_Int32& rDPIX, sal_Int32& rDPIY ) override;

    virtual void            SetTextColor( Color nColor ) override;
    virtual void            SetFont(LogicalFontInstance*, int nFallbackLevel) override;
    virtual void            GetFontMetric( ImplFontMetricDataRef&, int nFallbackLevel ) override;
    virtual FontCharMapRef  GetFontCharMap() const override;
    virtual bool            GetFontCapabilities(vcl::FontCapabilities &rFontCapabilities) const override;
    virtual void            GetDevFontList( vcl::font::PhysicalFontCollection* ) override;
    // graphics must drop any cached font info
    virtual void            ClearDevFontCache() override;
    virtual bool            AddTempDevFont( vcl::font::PhysicalFontCollection*,
                                            const OUString& rFileURL,
                                            const OUString& rFontName ) override;

    virtual std::unique_ptr<GenericSalLayout>
                            GetTextLayout(int nFallbackLevel) override;
    virtual void            DrawTextLayout( const GenericSalLayout& ) override;

    virtual SystemGraphicsData GetGraphicsData() const override;

#if ENABLE_CAIRO_CANVAS
    virtual bool            SupportsCairo() const override;
    virtual cairo::SurfaceSharedPtr CreateSurface(const cairo::CairoSurfaceSharedPtr& rSurface) const override;
    virtual cairo::SurfaceSharedPtr CreateSurface(const OutputDevice& rRefDevice, int x, int y, int width, int height) const override;
    virtual cairo::SurfaceSharedPtr CreateBitmapSurface(const OutputDevice& rRefDevice, const BitmapSystemData& rData, const Size& rSize) const override;
    virtual css::uno::Any   GetNativeSurfaceHandle(cairo::SurfaceSharedPtr& rSurface, const basegfx::B2ISize& rSize) const override;
#endif // ENABLE_CAIRO_CANVAS
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
