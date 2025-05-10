/* comment */
#pragma once

#include <headless/CairoCommon.hxx>
#include <headless/svpbmp.hxx>
#include <basegfx/utils/systemdependentdata.hxx>

class BitmapHelper : public SurfaceHelper
{
private:
#ifdef HAVE_CAIRO_FORMAT_RGB24_888
    const bool m_bForceARGB32;
#endif
    SvpSalBitmap aTmpBmp;

public:
    explicit BitmapHelper(const SalBitmap& rSourceBitmap, const bool bForceARGB32 = false);
    void mark_dirty();
    unsigned char* getBits(sal_Int32& rStride);
};

class MaskHelper : public SurfaceHelper
{
private:
    std::unique_ptr<unsigned char[]> pAlphaBits;

public:
    explicit MaskHelper(const SalBitmap& rAlphaBitmap);
};

class SystemDependentData_BitmapHelper : public basegfx::SystemDependentData
{
private:
    std::shared_ptr<BitmapHelper> maBitmapHelper;

public:
    SystemDependentData_BitmapHelper(std::shared_ptr<BitmapHelper> xBitmapHelper);

    const std::shared_ptr<BitmapHelper>& getBitmapHelper() const { return maBitmapHelper; };
    virtual sal_Int64 estimateUsageInBytes() const override;
};

class SystemDependentData_MaskHelper : public basegfx::SystemDependentData
{
private:
    std::shared_ptr<MaskHelper> maMaskHelper;

public:
    SystemDependentData_MaskHelper(std::shared_ptr<MaskHelper> xMaskHelper);

    const std::shared_ptr<MaskHelper>& getMaskHelper() const { return maMaskHelper; };
    virtual sal_Int64 estimateUsageInBytes() const override;
};

VCL_DLLPUBLIC void tryToUseSourceBuffer(const SalBitmap& rSourceBitmap,
                                        std::shared_ptr<BitmapHelper>& rSurface);
VCL_DLLPUBLIC void tryToUseMaskBuffer(const SalBitmap& rMaskBitmap,
                                      std::shared_ptr<MaskHelper>& rMask);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
