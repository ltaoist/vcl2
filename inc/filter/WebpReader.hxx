/* comment */
#pragma once

#include <vcl/graph.hxx>

VCL_DLLPUBLIC bool ImportWebpGraphic(SvStream& rStream, Graphic& rGraphic);

bool ReadWebpInfo(SvStream& rStream, Size& pixelSize, sal_uInt16& bitsPerPixel, bool& hasAlpha);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
