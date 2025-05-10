/* comment */
#ifndef VCL_INC_BITMAP_BITMAPSCALECONVOLUTIONFILTER_HXX
#define VCL_INC_BITMAP_BITMAPSCALECONVOLUTIONFILTER_HXX

#include <vcl/BitmapFilter.hxx>

#include <ResampleKernel.hxx>

namespace vcl
{
class BitmapScaleConvolutionFilter : public BitmapFilter
{
protected:
    BitmapScaleConvolutionFilter(const double& rScaleX, const double& rScaleY,
                                 std::unique_ptr<Kernel> pKernel)
        : mxKernel(std::move(pKernel))
        , mrScaleX(rScaleX)
        , mrScaleY(rScaleY)
    {
    }

    virtual BitmapEx execute(BitmapEx const& rBitmap) const override;

private:
    std::unique_ptr<Kernel> mxKernel;
    double mrScaleX;
    double mrScaleY;
};

class VCL_DLLPUBLIC BitmapScaleBilinearFilter final : public BitmapScaleConvolutionFilter
{
public:
    BitmapScaleBilinearFilter(const double& rScaleX, const double& rScaleY)
        : BitmapScaleConvolutionFilter(rScaleX, rScaleY, std::make_unique<BilinearKernel>())
    {
    }
};

class VCL_DLLPUBLIC BitmapScaleBicubicFilter final : public BitmapScaleConvolutionFilter
{
public:
    BitmapScaleBicubicFilter(const double& rScaleX, const double& rScaleY)
        : BitmapScaleConvolutionFilter(rScaleX, rScaleY, std::make_unique<BicubicKernel>())
    {
    }
};

class VCL_DLLPUBLIC BitmapScaleLanczos3Filter final : public BitmapScaleConvolutionFilter
{
public:
    BitmapScaleLanczos3Filter(const double& rScaleX, const double& rScaleY)
        : BitmapScaleConvolutionFilter(rScaleX, rScaleY, std::make_unique<Lanczos3Kernel>())
    {
    }
};
}

#endif // VCL_INC_BITMAPSCALECONVOLUTIONFILTER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
