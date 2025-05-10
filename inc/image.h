/* comment */
#ifndef INCLUDED_VCL_INC_IMAGE_H
#define INCLUDED_VCL_INC_IMAGE_H

#include <vcl/bitmapex.hxx>

class SalGraphics;

class ImplImage
{
private:
    BitmapChecksum maBitmapChecksum;
    /// if non-empty: cached original size of maStockName else Size of maBitmap
    Size maSizePixel;
    /// If set - defines the bitmap via images.zip*
    OUString maStockName;


    /// Original bitmap - or cache of a potentially scaled bitmap
    BitmapEx maBitmapEx;
    BitmapEx maDisabledBitmapEx;

    bool loadStockAtScale(SalGraphics* pGraphics, BitmapEx &rBitmapEx);

public:
    ImplImage(const BitmapEx& rBitmapEx);
    ImplImage(OUString aStockName);

    bool isStock() const
    {
        return maStockName.getLength() > 0;
    }

    const OUString & getStock() const
    {
        return maStockName;
    }

    /// get size in co-ordinates not scaled for HiDPI
    Size getSizePixel();
    /// Legacy - the original bitmap
    BitmapEx const & getBitmapEx(bool bDisabled = false);
    /// Taking account of HiDPI scaling
    BitmapEx const & getBitmapExForHiDPI(bool bDisabled, SalGraphics* pGraphics);

    bool isEqual(const ImplImage &ref) const;
    bool isSizeEmpty() const
    {
        return maSizePixel == Size();
    }
};

#endif // INCLUDED_VCL_INC_IMAGE_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
