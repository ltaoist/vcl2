/* comment */
#ifndef INCLUDED_VCL_SOURCE_FILTER_IXPM_XPMREAD_HXX
#define INCLUDED_VCL_SOURCE_FILTER_IXPM_XPMREAD_HXX

#include <tools/stream.hxx>
#include <vcl/dllapi.h>

class Graphic;

VCL_DLLPUBLIC bool ImportXPM(SvStream& rStream, Graphic& rGraphic);

#endif // INCLUDED_VCL_SOURCE_FILTER_IXPM_XPMREAD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
