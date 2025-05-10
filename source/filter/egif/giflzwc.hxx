/* comment */
#ifndef INCLUDED_FILTER_SOURCE_GRAPHICFILTER_EGIF_GIFLZWC_HXX
#define INCLUDED_FILTER_SOURCE_GRAPHICFILTER_EGIF_GIFLZWC_HXX

#include <vcl/mapmod.hxx>


class   GIFImageDataOutputStream;
struct  GIFLZWCTreeNode;


class GIFLZWCompressor
{
private:

    std::unique_ptr<GIFImageDataOutputStream> pIDOS;
    std::unique_ptr<GIFLZWCTreeNode[]> pTable;
    GIFLZWCTreeNode*            pPrefix;
    sal_uInt16                  nDataSize;
    sal_uInt16                  nClearCode;
    sal_uInt16                  nEOICode;
    sal_uInt16                  nTableSize;
    sal_uInt16                  nCodeSize;

public:

                                GIFLZWCompressor();
                                ~GIFLZWCompressor();

    void                        StartCompression( SvStream& rGIF, sal_uInt16 nPixelSize );
    void                        Compress(sal_uInt8* pSrc, sal_uInt32 nSize);
    void                        EndCompression();
};

#endif // INCLUDED_FILTER_SOURCE_GRAPHICFILTER_EGIF_GIFLZWC_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
