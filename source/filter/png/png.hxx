/* comment */
#pragma once

#include <vcl/graph.hxx>
#include <vcl/graphicfilter.hxx>

#include <bitmap/BitmapWriteAccess.hxx>

namespace vcl
{
bool ImportPNG(SvStream& rInputStream, Graphic& rGraphic, GraphicFilterImportFlags nImportFlags,
               BitmapScopedWriteAccess* pAccess, AlphaScopedWriteAccess* pAlphaAccess);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
