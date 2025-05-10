/* comment */
#ifndef INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEGREADER_HXX
#define INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEGREADER_HXX

#include <vcl/graph.hxx>
#include <vcl/bitmap.hxx>

#include <bitmap/BitmapWriteAccess.hxx>
#include <graphic/GraphicReader.hxx>

enum class GraphicFilterImportFlags;

enum ReadState
{
    JPEGREAD_OK,
    JPEGREAD_ERROR,
    JPEGREAD_NEED_MORE
};

struct JPEGCreateBitmapParam
{
    tools::ULong nWidth;
    tools::ULong nHeight;
    tools::ULong density_unit;
    tools::ULong X_density;
    tools::ULong Y_density;

    bool bGray;
};

class JPEGReader : public GraphicReader
{
    SvStream&           mrStream;
    std::unique_ptr<Bitmap> mpBitmap;
    std::unique_ptr<Bitmap> mpIncompleteAlpha;

    tools::Long                mnLastPos;
    tools::Long                mnLastLines;
    bool                mbSetLogSize;

    Graphic CreateIntermediateGraphic(tools::Long nLines);

public:
            JPEGReader( SvStream& rStream, GraphicFilterImportFlags nImportFlags );
    virtual ~JPEGReader() override;

    ReadState Read(Graphic& rGraphic, GraphicFilterImportFlags nImportFlags, BitmapScopedWriteAccess* ppAccess);

    bool CreateBitmap(JPEGCreateBitmapParam const & param);

    Bitmap& GetBitmap() { return *mpBitmap; }
};

#endif // INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEGREADER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
