/* comment */
#ifndef INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEG_H
#define INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEG_H

#include <sal/config.h>

#include <com/sun/star/uno/Reference.hxx>
#include <basegfx/vector/b2dsize.hxx>
#include <bitmap/BitmapWriteAccess.hxx>

#include <jpeglib.h>

namespace com::sun::star::task {
    class XStatusIndicator;
}
class JPEGReader;
class JPEGWriter;
class Size;
class SvStream;
enum class GraphicFilterImportFlags;

void jpeg_svstream_src (j_decompress_ptr cinfo, void* infile);

void jpeg_svstream_dest (j_compress_ptr cinfo, void* outfile);

bool    WriteJPEG( JPEGWriter* pJPEGWriter, void* pOutputStream,
                   tools::Long nWidth, tools::Long nHeight, basegfx::B2DSize const &  aPPI, bool bGreyScale,
                   tools::Long nQualityPercent, tools::Long aChromaSubsampling,
                   css::uno::Reference<css::task::XStatusIndicator> const & status);

void    ReadJPEG( JPEGReader* pJPEGReader, void* pInputStream, tools::Long* pLines,
                  GraphicFilterImportFlags nImportFlags,
                  BitmapScopedWriteAccess* ppAccess );

void    Transform(void* pInputStream, void* pOutputStream, Degree10 nAngle);

/* Expanded data source object for stdio input */

struct SourceManagerStruct {
    jpeg_source_mgr pub;                /* public fields */
    SvStream*   stream;                 /* source stream */
    JOCTET*     buffer;                 /* start of buffer */
    boolean     start_of_file;          /* have we gotten any data yet? */
    int         no_data_available_failures;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
