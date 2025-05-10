/* comment */
#include <vcl/GraphicNativeTransform.hxx>

#include <vcl/gfxlink.hxx>
#include <vcl/graphicfilter.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/uno/Sequence.hxx>
#include <tools/stream.hxx>
#include <comphelper/propertyvalue.hxx>

#include "jpeg/Exif.hxx"
#include "jpeg/JpegTransform.hxx"

GraphicNativeTransform::GraphicNativeTransform(Graphic& rGraphic)
    : mrGraphic(rGraphic)
{
}

void GraphicNativeTransform::rotate(Degree10 aInputRotation)
{
    // Rotation can be between 0 and 3600
    Degree10 aRotation = aInputRotation % 3600_deg10;

    if (aRotation == 0_deg10)
    {
        return; // No rotation is needed
    }
    else if (aRotation != 900_deg10 && aRotation != 1800_deg10 && aRotation != 2700_deg10)
    {
        return;
    }

    GfxLink aLink = mrGraphic.GetGfxLink();
    if (aLink.GetType() == GfxLinkType::NativeJpg)
    {
        rotateJPEG(aRotation);
    }
    else if (aLink.GetType() == GfxLinkType::NativePng)
    {
        rotateGeneric(aRotation, u"png");
    }
    else if (aLink.GetType() == GfxLinkType::NativeGif)
    {
        rotateGeneric(aRotation, u"gif");
    }
    else if (aLink.GetType() == GfxLinkType::NONE)
    {
        rotateBitmapOnly(aRotation);
    }
}

bool GraphicNativeTransform::rotateBitmapOnly(Degree10 aRotation)
{
    if (mrGraphic.IsAnimated())
    {
        return false;
    }

    BitmapEx aBitmap = mrGraphic.GetBitmapEx();
    aBitmap.Rotate(aRotation, COL_BLACK);
    mrGraphic = aBitmap;

    return true;
}

bool GraphicNativeTransform::rotateGeneric(Degree10 aRotation, std::u16string_view aType)
{
    // Can't rotate animations yet
    if (mrGraphic.IsAnimated())
    {
        return false;
    }

    SvMemoryStream aStream;

    GraphicFilter& rFilter = GraphicFilter::GetGraphicFilter();

    css::uno::Sequence<css::beans::PropertyValue> aFilterData{
        comphelper::makePropertyValue("Interlaced", sal_Int32(0)),
        comphelper::makePropertyValue("Compression", sal_Int32(9)),
        comphelper::makePropertyValue("Quality", sal_Int32(90))
    };

    sal_uInt16 nFilterFormat = rFilter.GetExportFormatNumberForShortName(aType);

    BitmapEx aBitmap = mrGraphic.GetBitmapEx();
    aBitmap.Rotate(aRotation, COL_BLACK);
    rFilter.ExportGraphic(aBitmap, u"none", aStream, nFilterFormat, &aFilterData);

    aStream.Seek(STREAM_SEEK_TO_BEGIN);

    Graphic aGraphic;
    rFilter.ImportGraphic(aGraphic, u"import", aStream);

    mrGraphic = aGraphic;
    return true;
}

void GraphicNativeTransform::rotateJPEG(Degree10 aRotation)
{
    BitmapEx aBitmap = mrGraphic.GetBitmapEx();

    if (aBitmap.GetSizePixel().Width() % 16 != 0 || aBitmap.GetSizePixel().Height() % 16 != 0)
    {
        rotateGeneric(aRotation, u"png");
    }
    else
    {
        GfxLink aLink = mrGraphic.GetGfxLink();

        SvMemoryStream aSourceStream;
        aSourceStream.WriteBytes(aLink.GetData(), aLink.GetDataSize());
        aSourceStream.Seek(STREAM_SEEK_TO_BEGIN);

        exif::Orientation aOrientation = exif::TOP_LEFT;

        Exif exif;
        if (exif.read(aSourceStream))
        {
            aOrientation = exif.getOrientation();
        }

        SvMemoryStream aTargetStream;
        JpegTransform transform(aSourceStream, aTargetStream);
        transform.setRotate(aRotation);
        transform.perform();

        aTargetStream.Seek(STREAM_SEEK_TO_BEGIN);

        // Reset orientation in exif if needed
        if (exif.hasExif() && aOrientation != exif::TOP_LEFT)
        {
            exif.setOrientation(exif::TOP_LEFT);
            exif.write(aTargetStream);
        }

        aTargetStream.Seek(STREAM_SEEK_TO_BEGIN);

        Graphic aGraphic;
        GraphicFilter& rFilter = GraphicFilter::GetGraphicFilter();
        rFilter.ImportGraphic(aGraphic, u"import", aTargetStream);
        mrGraphic = aGraphic;
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
