/* comment */
#ifndef INCLUDED_VCL_INC_BMPFAST_HXX
#define INCLUDED_VCL_INC_BMPFAST_HXX

#include <vcl/dllapi.h>
#include <vcl/Scanline.hxx>
#include <tools/long.hxx>

class BitmapWriteAccess;
class BitmapReadAccess;
struct BitmapBuffer;
class BitmapColor;
struct SalTwoRect;

// the bmpfast functions have signatures with good compatibility to
// their canonic counterparts, which employ the GetPixel/SetPixel methods

VCL_DLLPUBLIC bool ImplFastBitmapConversion( BitmapBuffer& rDst, const BitmapBuffer& rSrc,
        const SalTwoRect& rTwoRect );

bool ImplFastCopyScanline( tools::Long nY, BitmapBuffer& rDst, const BitmapBuffer& rSrc);
bool ImplFastCopyScanline( tools::Long nY, BitmapBuffer& rDst, ConstScanline aSrcScanline,
    ScanlineFormat nSrcScanlineFormat, sal_uInt32 nSrcScanlineSize);

bool ImplFastBitmapBlending( BitmapWriteAccess const & rDst,
    const BitmapReadAccess& rSrc, const BitmapReadAccess& rMask,
    const SalTwoRect& rTwoRect );

bool ImplFastEraseBitmap( BitmapBuffer&, const BitmapColor& );

#endif // INCLUDED_VCL_INC_BMPFAST_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
