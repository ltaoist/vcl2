/* comment */
#ifndef INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IDXF_DXFREPRD_HXX
#define INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IDXF_DXFREPRD_HXX

#include "dxfblkrd.hxx"
#include "dxftblrd.hxx"
#include <array>
#include <string_view>

//--------------------Other stuff---------------------------------------------


//-------------------A 3D-Min/Max-Box-----------------------------------------

class DXFBoundingBox {
public:
    bool bEmpty;
    double fMinX;
    double fMinY;
    double fMinZ;
    double fMaxX;
    double fMaxY;
    double fMaxZ;

    DXFBoundingBox():bEmpty(true), fMinX(0.0), fMinY(0.0), fMinZ(0.0), fMaxX(0.0), fMaxY(0.0), fMaxZ(0.0) {}
    void Union(const DXFVector & rVector);
};


//-------------------The (constant) palette for DXF-------------------------

class DXFPalette {

public:

    DXFPalette();

    sal_uInt8 GetRed(sal_uInt8 nIndex) const;
    sal_uInt8 GetGreen(sal_uInt8 nIndex) const;
    sal_uInt8 GetBlue(sal_uInt8 nIndex) const;

private:
    std::array<sal_uInt8, 256> pRed;
    std::array<sal_uInt8, 256> pGreen;
    std::array<sal_uInt8, 256> pBlue;
    void SetColor(sal_uInt8 nIndex, sal_uInt8 nRed, sal_uInt8 nGreen, sal_uInt8 nBlue);
};


//-----------------read and represent DXF file--------------------------------


class DXFRepresentation {

public:

    DXFPalette aPalette;
        // The always equal DXF color palette

    DXFBoundingBox aBoundingBox;
        // is equal to the AutoCAD variables EXTMIN, EXTMAX if those exist
        // within the DXF file. Otherwise the BoundingBox gets calculated (in Read())

    DXFTables aTables;
        // the tables of the DXF file

    DXFBlocks aBlocks;
        // the blocks of the DXF file

    DXFEntities aEntities;
        // the entities (from the Entities-Section) of the DXF file

    rtl_TextEncoding mEnc;  // $DWGCODEPAGE

    double mfGlobalLineTypeScale; // $LTSCALE

    bool mbInCalc;  // guard for self-recursive bounding box calc

    DXFRepresentation();
    ~DXFRepresentation();

    rtl_TextEncoding getTextEncoding() const;
    void setTextEncoding(rtl_TextEncoding aEnc) { mEnc = aEnc; }
    OUString ToOUString(std::string_view s) const;

    double getGlobalLineTypeScale() const { return mfGlobalLineTypeScale; }
    void setGlobalLineTypeScale(double fGlobalLineTypeScale) { mfGlobalLineTypeScale = fGlobalLineTypeScale; }

    bool Read( SvStream & rIStream );
        // Reads complete DXF file.

private:
    void ReadHeader(DXFGroupReader & rDGR);
    void CalcBoundingBox(const DXFEntities & rEntities,
                         DXFBoundingBox & rBox);

    bool isTextEncodingSet() const { return mEnc != RTL_TEXTENCODING_DONTKNOW; }
};


//-------------------inlines--------------------------------------------------


inline sal_uInt8 DXFPalette::GetRed(sal_uInt8 nIndex) const { return pRed[nIndex]; }
inline sal_uInt8 DXFPalette::GetGreen(sal_uInt8 nIndex) const { return pGreen[nIndex]; }
inline sal_uInt8 DXFPalette::GetBlue(sal_uInt8 nIndex) const { return pBlue[nIndex]; }

#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
