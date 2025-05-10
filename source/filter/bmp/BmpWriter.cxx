/* comment */
#include <filter/BmpWriter.hxx>
#include <vcl/dibtools.hxx>

bool BmpWriter(SvStream& rStream, const Graphic& rGraphic, FilterConfigItem* pFilterConfigItem)
{
    BitmapEx aBitmap = rGraphic.GetBitmapEx();
    sal_Int32 nColor = pFilterConfigItem->ReadInt32("Color", 0);

    auto nColorRes = static_cast<BmpConversion>(nColor);
    if (nColorRes != BmpConversion::NNONE && nColorRes <= BmpConversion::N24Bit)
    {
        if (!aBitmap.Convert(nColorRes))
            aBitmap = rGraphic.GetBitmapEx();
    }
    bool bRleCoding = pFilterConfigItem->ReadBool("RLE_Coding", true);
    WriteDIB(aBitmap, rStream, bRleCoding);

    return rStream.good();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
