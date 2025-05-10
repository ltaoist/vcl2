/* comment */
#pragma once

#include <vcl/graph.hxx>
#include <sal/config.h>

class GDIMetaFile;
class SvStream;

VCL_DLLPUBLIC bool ImportPictGraphic(SvStream& rStream, Graphic& rGraphic);

/// Function to access PictReader::ReadPict for unit testing.
VCL_DLLPUBLIC void ReadPictFile(SvStream& rStreamPict, GDIMetaFile& rGDIMetaFile);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
