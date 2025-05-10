/* comment */
#ifndef INCLUDED_VCL_SOURCE_FILTER_IGIF_GIFREAD_HXX
#define INCLUDED_VCL_SOURCE_FILTER_IGIF_GIFREAD_HXX

#include <vcl/graph.hxx>

VCL_DLLPUBLIC bool ImportGIF(SvStream& rStream, Graphic& rGraphic);
bool IsGIFAnimated(SvStream& rStream, Size& rLogicSize);

#endif // INCLUDED_VCL_SOURCE_FILTER_IGIF_GIFREAD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
