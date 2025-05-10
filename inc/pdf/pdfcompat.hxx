/* comment */

#pragma once

#include <config_features.h>
#include <tools/gen.hxx>
#include <tools/stream.hxx>
#include <tools/UnitConversion.hxx>
#include <vcl/graph.hxx>

namespace vcl::pdf
{
/// Convert to inch, then assume 96 DPI.
inline double pointToPixel(const double fPoint, const double fResolutionDPI)
{
    return o3tl::convert(fPoint, o3tl::Length::pt, o3tl::Length::in) * fResolutionDPI;
}

/// Decide if PDF data is old enough to be compatible.
bool isCompatible(SvStream& rInStream, sal_uInt64 nPos, sal_uInt64 nSize);

/// Converts to highest supported format version (currently 1.6).
/// Usually used to deal with missing referenced objects in the
/// source pdf stream.
bool convertToHighestSupported(SvStream& rInStream, SvStream& rOutStream);

/// Takes care of transparently downgrading the version of the PDF stream in
/// case it's too new for our PDF export.
bool getCompatibleStream(SvStream& rInStream, SvStream& rOutStream);

BinaryDataContainer createBinaryDataContainer(SvStream& rStream);

} // end of vcl::filter::ipdf namespace

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
