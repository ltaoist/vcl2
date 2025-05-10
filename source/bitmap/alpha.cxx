/* comment */
#include <tools/color.hxx>
#include <vcl/alpha.hxx>

#include <bitmap/BitmapWriteAccess.hxx>
#include <salinst.hxx>
#include <svdata.hxx>
#include <salbmp.hxx>
#include <sal/log.hxx>

AlphaMask::AlphaMask() = default;

AlphaMask::AlphaMask( const Bitmap& rBitmap ) :
    Bitmap( rBitmap )
{
    if( !rBitmap.IsEmpty() )
        Convert( BmpConversion::N8BitNoConversion );
}

AlphaMask::AlphaMask( const AlphaMask& ) = default;

AlphaMask::AlphaMask( AlphaMask&& ) = default;

AlphaMask::AlphaMask( const Size& rSizePixel, const sal_uInt8* pEraseTransparency )
    : Bitmap(rSizePixel, vcl::PixelFormat::N8_BPP, &Bitmap::GetGreyPalette(256))
{
    if( pEraseTransparency )
        Bitmap::Erase( Color( *pEraseTransparency, *pEraseTransparency, *pEraseTransparency ) );
}

AlphaMask::~AlphaMask() = default;

AlphaMask& AlphaMask::operator=( const Bitmap& rBitmap )
{
    *static_cast<Bitmap*>(this) = rBitmap;

    if( !rBitmap.IsEmpty() )
        Convert( BmpConversion::N8BitNoConversion );

    return *this;
}

const Bitmap& AlphaMask::ImplGetBitmap() const
{
    return *this;
}

void AlphaMask::ImplSetBitmap( const Bitmap& rBitmap )
{
    SAL_WARN_IF(rBitmap.getPixelFormat() != vcl::PixelFormat::N8_BPP, "vcl.gdi", "Bitmap should be 8bpp, not " << vcl::pixelFormatBitCount(rBitmap.getPixelFormat()) << "bpp" );
    SAL_WARN_IF( !rBitmap.HasGreyPalette8Bit(), "vcl.gdi", "Bitmap isn't greyscale" );
    *static_cast<Bitmap*>(this) = rBitmap;
}

Bitmap const & AlphaMask::GetBitmap() const
{
    return ImplGetBitmap();
}

void AlphaMask::Erase( sal_uInt8 cTransparency )
{
    Bitmap::Erase( Color( cTransparency, cTransparency, cTransparency ) );
}

void AlphaMask::BlendWith(const Bitmap& rOther)
{
    std::shared_ptr<SalBitmap> xImpBmp(ImplGetSVData()->mpDefInst->CreateSalBitmap());
    if (xImpBmp->Create(*ImplGetSalBitmap()) && xImpBmp->AlphaBlendWith(*rOther.ImplGetSalBitmap()))
    {
        ImplSetSalBitmap(xImpBmp);
        return;
    }
    AlphaMask aOther(rOther); // to 8 bits
    Bitmap::ScopedReadAccess pOtherAcc(aOther);
    AlphaScopedWriteAccess pAcc(*this);
    if (!(pOtherAcc && pAcc && pOtherAcc->GetBitCount() == 8 && pAcc->GetBitCount() == 8))
        return;

    const tools::Long nHeight = std::min(pOtherAcc->Height(), pAcc->Height());
    const tools::Long nWidth = std::min(pOtherAcc->Width(), pAcc->Width());
    for (tools::Long y = 0; y < nHeight; ++y)
    {
        Scanline scanline = pAcc->GetScanline( y );
        ConstScanline otherScanline = pOtherAcc->GetScanline( y );
        for (tools::Long x = 0; x < nWidth; ++x)
        {
            // Use sal_uInt16 for following multiplication
            const sal_uInt16 nGrey1 = *scanline;
            const sal_uInt16 nGrey2 = *otherScanline;
            *scanline = static_cast<sal_uInt8>(nGrey1 + nGrey2 - nGrey1 * nGrey2 / 255);
            ++scanline;
            ++otherScanline;
        }
    }
}

void AlphaMask::ReleaseAccess( BitmapReadAccess* pAccess )
{
    if( pAccess )
    {
        Bitmap::ReleaseAccess( pAccess );
        Convert( BmpConversion::N8BitNoConversion );
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
