/* comment */
#include <filter/BmpReader.hxx>
#include <vcl/TypeSerializer.hxx>

bool BmpReader(SvStream& rStream, Graphic& rGraphic)
{
    TypeSerializer aSerializer(rStream);
    aSerializer.readGraphic(rGraphic);
    return !rStream.GetError();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
