/* comment */

#include <filter/DxfReader.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/graph.hxx>
#include "dxf2mtf.hxx"

//================== GraphicImport - the exported function ================

bool ImportDxfGraphic(SvStream & rStream, Graphic & rGraphic)
{
    DXFRepresentation aDXF;
    DXF2GDIMetaFile aConverter;
    GDIMetaFile aMTF;

    if ( !aDXF.Read( rStream ) )
        return false;
    if ( !aConverter.Convert( aDXF, aMTF, 60, 100 ) )
        return false;
    rGraphic = Graphic(aMTF);

    return true;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
