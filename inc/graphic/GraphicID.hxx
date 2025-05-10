/* comment */
#pragma once

#include <vcl/dllapi.h>
#include <rtl/string.hxx>
#include <vcl/checksum.hxx>

class ImpGraphic;

class GraphicID
{
private:
    sal_uInt32 mnID1;
    sal_uInt32 mnID2;
    sal_uInt32 mnID3;
    BitmapChecksum mnID4;

public:
    GraphicID(ImpGraphic const& rGraphic);

    bool operator==(const GraphicID& rID) const
    {
        return rID.mnID1 == mnID1 && rID.mnID2 == mnID2 && rID.mnID3 == mnID3 && rID.mnID4 == mnID4;
    }

    OString getIDString() const;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
