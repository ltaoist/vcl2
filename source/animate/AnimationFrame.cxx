/* comment */
#include <sal/config.h>
#include <o3tl/underlyingenumvalue.hxx>
#include <tools/solar.h>
#include <vcl/animate/AnimationFrame.hxx>

BitmapChecksum AnimationFrame::GetChecksum() const
{
    BitmapChecksum nCrc = maBitmapEx.GetChecksum();
    SVBT32 aBT32;

    Int32ToSVBT32(maPositionPixel.X(), aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    Int32ToSVBT32(maPositionPixel.Y(), aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    Int32ToSVBT32(maSizePixel.Width(), aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    Int32ToSVBT32(maSizePixel.Height(), aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    Int32ToSVBT32(mnWait, aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    UInt32ToSVBT32(o3tl::to_underlying(meDisposal), aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    UInt32ToSVBT32(sal_uInt32(mbUserInput), aBT32);
    nCrc = vcl_get_checksum(nCrc, aBT32, 4);

    return nCrc;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
