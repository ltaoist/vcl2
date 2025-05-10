/* comment */
#include "JpegReader.hxx"
#include "JpegWriter.hxx"
#include "jpeg.hxx"

#include <vcl/graphicfilter.hxx>

VCL_DLLPUBLIC bool ImportJPEG( SvStream& rInputStream, Graphic& rGraphic, GraphicFilterImportFlags nImportFlags, BitmapScopedWriteAccess* ppAccess )
{
    bool        bReturn = true;

    std::shared_ptr<GraphicReader> pContext = rGraphic.GetReaderContext();
    rGraphic.SetReaderContext(nullptr);
    JPEGReader* pJPEGReader = dynamic_cast<JPEGReader*>( pContext.get() );
    if (!pJPEGReader)
    {
        pContext = std::make_shared<JPEGReader>( rInputStream, nImportFlags );
        pJPEGReader = static_cast<JPEGReader*>( pContext.get() );
    }

    ReadState eReadState = pJPEGReader->Read( rGraphic, nImportFlags, ppAccess );

    if( eReadState == JPEGREAD_ERROR )
    {
        bReturn = false;
    }
    else if( eReadState == JPEGREAD_NEED_MORE )
    {
        rGraphic.SetReaderContext( pContext );
    }

    return bReturn;
}

bool ExportJPEG(SvStream& rOutputStream, const Graphic& rGraphic,
                    const css::uno::Sequence<css::beans::PropertyValue>* pFilterData,
                    bool* pExportWasGrey)
{
    JPEGWriter aJPEGWriter( rOutputStream, pFilterData, pExportWasGrey );
    bool bReturn = aJPEGWriter.Write( rGraphic );
    return bReturn;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
