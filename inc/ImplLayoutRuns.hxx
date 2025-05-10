/* comment */
#pragma once

#include <vcl/dllapi.h>
#include <boost/container/small_vector.hpp>

// used for managing runs e.g. for BiDi, glyph and script fallback
class VCL_DLLPUBLIC ImplLayoutRuns
{
private:
    int mnRunIndex;
    boost::container::small_vector<int, 8> maRuns;

public:
    ImplLayoutRuns() { mnRunIndex = 0; }

    void Clear() { maRuns.clear(); }
    void AddPos(int nCharPos, bool bRTL);
    void AddRun(int nMinRunPos, int nEndRunPos, bool bRTL);

    bool IsEmpty() const { return maRuns.empty(); }
    void ResetPos() { mnRunIndex = 0; }
    void NextRun() { mnRunIndex += 2; }
    bool GetRun(int* nMinRunPos, int* nEndRunPos, bool* bRTL) const;
    bool GetNextPos(int* nCharPos, bool* bRTL);
    bool PosIsInRun(int nCharPos) const;
    bool PosIsInAnyRun(int nCharPos) const;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
