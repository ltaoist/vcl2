/* comment */
#include "emfwr.hxx"
#include "wmfwr.hxx"
#include <vcl/wmf.hxx>
#include <vcl/gdimetafiletools.hxx>
#include <vcl/graph.hxx>

using namespace com::sun::star;

bool ReadWindowMetafile( SvStream& rStream, GDIMetaFile& rMTF )
{
    // tdf#111484 Use new method to import Metafile. Take current StreamPos
    // into account (used by SwWW8ImplReader::ReadGrafFile and by
    // SwWw6ReadMetaStream, so do *not* ignore. OTOH XclImpDrawing::ReadWmf
    // is nice enough to copy to an own MemStream to avoid that indirect
    // parameter passing...)
    const sal_uInt32 nStreamStart(rStream.Tell());
    const sal_uInt32 nStreamEnd(rStream.TellEnd());

    if (nStreamStart >= nStreamEnd)
    {
        return false;
    }

    // Read binary data to mem array
    const sal_uInt32 nStreamLength(nStreamEnd - nStreamStart);
    auto rData = std::make_unique<std::vector<sal_uInt8>>(nStreamLength);
    rStream.ReadBytes(rData->data(), rData->size());
    BinaryDataContainer aDataContainer(std::move(rData));
    rStream.Seek(nStreamStart);

    if (rStream.good())
    {
        // Throw into VectorGraphicData to get the import. Do not care
        // too much for type, this will be checked there. Also no path
        // needed, it is a temporary object
        auto aVectorGraphicDataPtr =
            std::make_shared<VectorGraphicData>(aDataContainer, VectorGraphicDataType::Emf);

        // create a Graphic and grep Metafile from it
        const Graphic aGraphic(aVectorGraphicDataPtr);

        // get the Metafile from it, done
        rMTF = aGraphic.GetGDIMetaFile();
        return true;
    }

    return rStream.good();
}

bool ConvertGDIMetaFileToWMF( const GDIMetaFile & rMTF, SvStream & rTargetStream,
                              FilterConfigItem const * pConfigItem, bool bPlaceable)
{
    WMFWriter aWMFWriter;
    GDIMetaFile aGdiMetaFile(rMTF);

    if(usesClipActions(aGdiMetaFile))
    {
        // #i121267# It is necessary to prepare the metafile since the export does *not* support
        // clip regions. This tooling method clips the geometry content of the metafile internally
        // against its own clip regions, so that the export is safe to ignore clip regions
        clipMetafileContentAgainstOwnRegions(aGdiMetaFile);
    }

    bool bRet = aWMFWriter.WriteWMF(aGdiMetaFile, rTargetStream, pConfigItem, bPlaceable);
    return bRet;
}

bool ConvertGraphicToWMF(const Graphic& rGraphic, SvStream& rTargetStream,
                         FilterConfigItem const* pConfigItem, bool bPlaceable)
{
    GfxLink aLink = rGraphic.GetGfxLink();
    if (aLink.GetType() == GfxLinkType::NativeWmf && aLink.GetData() && aLink.GetDataSize())
    {
        if(!aLink.IsEMF()) // If WMF, just write directly.
            return rTargetStream.WriteBytes(aLink.GetData(), aLink.GetDataSize()) == aLink.GetDataSize();

        // This may be an EMF+ file. In EmfReader::ReadEnhWMF() we normally drop non-EMF commands
        // when reading EMF+, so converting that to WMF is better done by re-parsing with EMF+ disabled.
        auto & rDataContainer = aLink.getDataContainer();
        auto aVectorGraphicData
            = std::make_shared<VectorGraphicData>(rDataContainer, VectorGraphicDataType::Emf);
        aVectorGraphicData->setEnableEMFPlus(false);
        Graphic aGraphic(aVectorGraphicData);
        bool bRet = ConvertGDIMetaFileToWMF(aGraphic.GetGDIMetaFile(), rTargetStream, pConfigItem,
                                            bPlaceable);
        return bRet;
    }

    bool bRet = ConvertGDIMetaFileToWMF(rGraphic.GetGDIMetaFile(), rTargetStream, pConfigItem,
                                        bPlaceable);
    return bRet;
}

bool ConvertGDIMetaFileToEMF(const GDIMetaFile & rMTF, SvStream & rTargetStream)
{
    EMFWriter aEMFWriter(rTargetStream);
    GDIMetaFile aGdiMetaFile(rMTF);

    if(usesClipActions(aGdiMetaFile))
    {
        // #i121267# It is necessary to prepare the metafile since the export does *not* support
        // clip regions. This tooling method clips the geometry content of the metafile internally
        // against its own clip regions, so that the export is safe to ignore clip regions
        clipMetafileContentAgainstOwnRegions(aGdiMetaFile);
    }

    return aEMFWriter.WriteEMF(aGdiMetaFile);
}

bool WriteWindowMetafileBits( SvStream& rStream, const GDIMetaFile& rMTF )
{
    return WMFWriter().WriteWMF( rMTF, rStream, nullptr, false );
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
