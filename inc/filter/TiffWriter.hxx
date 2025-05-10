/* comment */
#pragma once

#include <vcl/graph.hxx>
#include <vcl/FilterConfigItem.hxx>

VCL_DLLPUBLIC bool ExportTiffGraphicImport(SvStream& rStream, const Graphic& rGraphic,
                                           const FilterConfigItem* pFilterConfigItem);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
