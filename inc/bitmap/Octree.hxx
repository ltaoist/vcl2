/* comment */
#ifndef INCLUDED_VCL_INC_OCTREE_HXX
#define INCLUDED_VCL_INC_OCTREE_HXX

#include <vcl/dllapi.h>
#include <vcl/BitmapColor.hxx>
#include <tools/solar.h>

struct OctreeNode
{
    sal_uLong nCount = 0;
    sal_uLong nRed = 0;
    sal_uLong nGreen = 0;
    sal_uLong nBlue = 0;
    std::unique_ptr<OctreeNode> pChild[8];
    OctreeNode* pNext = nullptr;
    sal_uInt16 nPalIndex = 0;
    bool bLeaf = false;
};

class BitmapReadAccess;

class VCL_PLUGIN_PUBLIC Octree
{
private:
    void CreatePalette(OctreeNode* pNode);
    void GetPalIndex(const OctreeNode* pNode, BitmapColor const& color);

    SAL_DLLPRIVATE void add(std::unique_ptr<OctreeNode>& rpNode, BitmapColor const& color);
    SAL_DLLPRIVATE void reduce();

    BitmapPalette maPalette;
    sal_uLong mnLeafCount;
    sal_uLong mnLevel;
    std::unique_ptr<OctreeNode> pTree;
    std::vector<OctreeNode*> mpReduce;
    sal_uInt16 mnPalIndex;

public:
    Octree(const BitmapReadAccess& rReadAcc, sal_uLong nColors);
    ~Octree();

    const BitmapPalette& GetPalette();
    sal_uInt16 GetBestPaletteIndex(const BitmapColor& rColor);
};

class InverseColorMap
{
private:
    std::vector<sal_uInt8> mpBuffer;
    std::vector<sal_uInt8> mpMap;

    void ImplCreateBuffers();

public:
    explicit InverseColorMap(const BitmapPalette& rPal);
    ~InverseColorMap();

    sal_uInt16 GetBestPaletteIndex(const BitmapColor& rColor);
};

#endif // INCLUDED_VCL_INC_OCTREE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
