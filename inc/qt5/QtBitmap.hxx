/* comment */
#pragma once

#include <salbmp.hxx>

#include <memory>

class QImage;

class QtBitmap final : public SalBitmap
{
    std::unique_ptr<QImage> m_pImage;
    BitmapPalette m_aPalette;

public:
    QtBitmap();
    QtBitmap(const QImage& rQImage);

    const QImage* GetQImage() const { return m_pImage.get(); }

    virtual bool Create(const Size& rSize, vcl::PixelFormat ePixelFormat,
                        const BitmapPalette& rPal) override;
    virtual bool Create(const SalBitmap& rSalBmp) override;
    virtual bool Create(const SalBitmap& rSalBmp, SalGraphics* pGraphics) override;
    virtual bool Create(const SalBitmap& rSalBmp, vcl::PixelFormat eNewPixelFormat) override;
    virtual bool Create(const css::uno::Reference<css::rendering::XBitmapCanvas>& rBitmapCanvas,
                        Size& rSize, bool bMask = false) override;
    virtual void Destroy() final override;
    virtual Size GetSize() const override;
    virtual sal_uInt16 GetBitCount() const override;

    virtual BitmapBuffer* AcquireBuffer(BitmapAccessMode nMode) override;
    virtual void ReleaseBuffer(BitmapBuffer* pBuffer, BitmapAccessMode nMode) override;
    virtual bool GetSystemData(BitmapSystemData& rData) override;

    virtual bool ScalingSupported() const override;
    virtual bool Scale(const double& rScaleX, const double& rScaleY,
                       BmpScaleFlag nScaleFlag) override;
    virtual bool Replace(const Color& rSearchColor, const Color& rReplaceColor,
                         sal_uInt8 nTol) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
