/* comment */
#pragma once

#include <vcl/graph.hxx>
#include <vcl/FilterConfigItem.hxx>

VCL_DLLPUBLIC bool ExportEpsGraphic(SvStream& rStream, const Graphic& rGraphic,
                                    FilterConfigItem* pFilterConfigItem);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
