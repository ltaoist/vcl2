/* comment */
#ifndef INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IDXF_DXFBLKRD_HXX
#define INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IDXF_DXFBLKRD_HXX

#include <sal/config.h>

#include <string_view>

#include "dxfentrd.hxx"


//---------------- A Block (= Set of Entities) --------------------------


class DXFBlock : public DXFEntities {

public:

    DXFBlock * pSucc;
        // pointer to the next block in the list DXFBlocks::pFirst

    // properties of blocks; commented with group codes:
    OString m_sName;                      //  2
    OString m_sAlsoName;                  //  3
    tools::Long nFlags;                          // 70
    DXFVector aBasePoint;                 // 10,20,30
    OString m_sXRef;                      //  1

    DXFBlock();
    ~DXFBlock();

    void Read(DXFGroupReader & rDGR);
        // reads the block (including entities) from a dxf file
        // by rGDR until an ENDBLK, ENDSEC or EOF.
};


//---------------- A set of blocks -----------------------------------


class DXFBlocks {

    DXFBlock * pFirst;
        // list of blocks, READ ONLY!

public:

    DXFBlocks();
    ~DXFBlocks();

    void Read(DXFGroupReader & rDGR);
        // reads all block per rDGR until an ENDSEC or EOF.

    DXFBlock * Search(std::string_view rName) const;
        // looks for a block with the name, return NULL if not successful

    void Clear();
        // deletes all blocks

};

#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
