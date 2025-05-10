/* comment */
#ifndef INCLUDED_VCL_INC_BITMAP_BITMAPSCALESUPER_HXX
#define INCLUDED_VCL_INC_BITMAP_BITMAPSCALESUPER_HXX

#include <vcl/BitmapFilter.hxx>

class BitmapScaleSuperFilter final : public BitmapFilter
{
public:
    BitmapScaleSuperFilter(const double& rScaleX, const double& rScaleY);
    virtual ~BitmapScaleSuperFilter() override;

    virtual BitmapEx execute(BitmapEx const& rBitmap) const override;

private:
    double mrScaleX;
    double mrScaleY;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
