/* comment */
#include <vcl/GraphicNativeMetadata.hxx>
#include <vcl/gfxlink.hxx>
#include "jpeg/Exif.hxx"
#include <memory>

GraphicNativeMetadata::GraphicNativeMetadata()
    : mRotation(0)
{
}

bool GraphicNativeMetadata::read(Graphic const& rGraphic)
{
    GfxLink aLink = rGraphic.GetGfxLink();
    if (aLink.GetType() != GfxLinkType::NativeJpg)
        return false;

    sal_uInt32 aDataSize = aLink.GetDataSize();
    if (!aDataSize)
        return false;

    std::unique_ptr<sal_uInt8[]> aBuffer(new sal_uInt8[aDataSize]);

    memcpy(aBuffer.get(), aLink.GetData(), aDataSize);
    SvMemoryStream aMemoryStream(aBuffer.get(), aDataSize, StreamMode::READ);

    read(aMemoryStream);

    return true;
}

bool GraphicNativeMetadata::read(SvStream& rStream)
{
    Exif aExif;
    aExif.read(rStream);
    mRotation = aExif.getRotation();

    return true;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
