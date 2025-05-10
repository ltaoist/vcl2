/* comment */
#ifndef INCLUDED_VCL_INC_HEADLESS_SVPBMP_HXX
#define INCLUDED_VCL_INC_HEADLESS_SVPBMP_HXX

#include <sal/config.h>

#include <salbmp.hxx>
#include <basegfx/utils/systemdependentdata.hxx>

class VCL_DLLPUBLIC SvpSalBitmap final : public SalBitmap, public basegfx::SystemDependentDataHolder // MM02
{
    std::unique_ptr<BitmapBuffer> mpDIB;
public:
             SvpSalBitmap();
    virtual ~SvpSalBitmap() override;

    // SalBitmap
    virtual bool            Create(const Size& rSize,
                                   vcl::PixelFormat ePixelFormat,
                                   const BitmapPalette& rPalette) override;
    virtual bool            Create( const SalBitmap& rSalBmp ) override;
    virtual bool            Create( const SalBitmap& rSalBmp,
                                    SalGraphics* pGraphics ) override;
    virtual bool            Create(const SalBitmap& rSalBmp,
                                   vcl::PixelFormat eNewPixelFormat) override;
    virtual bool            Create( const css::uno::Reference< css::rendering::XBitmapCanvas >& rBitmapCanvas,
                                    Size& rSize,
                                    bool bMask = false ) override;
    void                    Create(std::unique_ptr<BitmapBuffer> pBuf);
    const BitmapBuffer*     GetBuffer() const
    {
        return mpDIB.get();
    }
    virtual void            Destroy() final override;
    virtual Size            GetSize() const override;
    virtual sal_uInt16      GetBitCount() const override;

    virtual BitmapBuffer*   AcquireBuffer( BitmapAccessMode nMode ) override;
    virtual void            ReleaseBuffer( BitmapBuffer* pBuffer, BitmapAccessMode nMode ) override;
    virtual bool            GetSystemData( BitmapSystemData& rData ) override;

    virtual bool            ScalingSupported() const override;
    virtual bool            Scale( const double& rScaleX, const double& rScaleY, BmpScaleFlag nScaleFlag ) override;
    virtual bool            Replace( const Color& rSearchColor, const Color& rReplaceColor, sal_uInt8 nTol ) override;

    virtual const basegfx::SystemDependentDataHolder* accessSystemDependentDataHolder() const override;
};

#endif // INCLUDED_VCL_INC_HEADLESS_SVPBMP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
