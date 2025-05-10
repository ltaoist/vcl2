/* comment */
#ifndef INCLUDED_VCL_INC_SCANLINEWRITER_HXX
#define INCLUDED_VCL_INC_SCANLINEWRITER_HXX

#include <vcl/bitmap.hxx>
#include <vcl/BitmapPalette.hxx>

namespace vcl
{
// Write color information for 1, 4 and 8 bit palette bitmap scanlines.
class ScanlineWriter
{
    BitmapPalette& maPalette;
    sal_uInt8 const mnColorsPerByte; // number of colors that are stored in one byte
    sal_uInt8 const mnColorBitSize; // number of bits a color takes
    sal_uInt8 const mnColorBitMask; // bit mask used to isolate the color
    sal_uInt8* mpCurrentScanline;
    tools::Long mnX;

public:
    ScanlineWriter(BitmapPalette& aPalette, sal_Int8 nColorsPerByte)
        : maPalette(aPalette)
        , mnColorsPerByte(nColorsPerByte)
        , mnColorBitSize(
              8
              / mnColorsPerByte) // bit size is number of bit in a byte divided by number of colors per byte (8 / 2 = 4 for 4-bit)
        , mnColorBitMask((1 << mnColorBitSize) - 1) // calculate the bit mask from the bit size
        , mpCurrentScanline(nullptr)
        , mnX(0)
    {
    }

    static std::unique_ptr<ScanlineWriter> Create(sal_uInt16 nBits, BitmapPalette& aPalette)
    {
        switch (nBits)
        {
            case 1:
                return std::make_unique<ScanlineWriter>(aPalette, 8);
            case 4:
                return std::make_unique<ScanlineWriter>(aPalette, 2);
            case 8:
                return std::make_unique<ScanlineWriter>(aPalette, 1);
            default:
                abort();
        }
    }

    void writeRGB(sal_uInt8 nR, sal_uInt8 nG, sal_uInt8 nB)
    {
        // calculate to which index we will write
        tools::Long nScanlineIndex = mnX / mnColorsPerByte;

        // calculate the number of shifts to get the color information to the right place
        tools::Long nShift = (8 - mnColorBitSize) - ((mnX % mnColorsPerByte) * mnColorBitSize);

        sal_uInt16 nColorIndex = maPalette.GetBestIndex(BitmapColor(nR, nG, nB));
        mpCurrentScanline[nScanlineIndex] &= ~(mnColorBitMask << nShift); // clear
        mpCurrentScanline[nScanlineIndex] |= (nColorIndex & mnColorBitMask) << nShift; // set
        mnX++;
    }

    void nextLine(sal_uInt8* pScanline)
    {
        mnX = 0;
        mpCurrentScanline = pScanline;
    }
};

} // namespace vcl

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
