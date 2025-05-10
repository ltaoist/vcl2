/* comment */
#ifndef INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEG_HXX
#define INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEG_HXX

#include <vcl/graph.hxx>
#include <vcl/graphicfilter.hxx>

#include <bitmap/BitmapWriteAccess.hxx>

#include <com/sun/star/uno/Sequence.h>

VCL_DLLPUBLIC bool ImportJPEG( SvStream& rInputStream, Graphic& rGraphic, GraphicFilterImportFlags nImportFlags, BitmapScopedWriteAccess* ppAccess );

bool ExportJPEG(SvStream& rOutputStream,
                    const Graphic& rGraphic,
                    const css::uno::Sequence< css::beans::PropertyValue >* pFilterData,
                    bool* pExportWasGrey);

#endif // INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEG_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
