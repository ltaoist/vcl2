/* comment */
#pragma once

#include <tools/stream.hxx>
#include <vcl/graph.hxx>
#include <vcl/FilterConfigItem.hxx>

VCL_DLLPUBLIC bool ExportWebpGraphic(SvStream& rStream, const Graphic& rGraphic,
                                     FilterConfigItem* pFilterConfigItem);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
