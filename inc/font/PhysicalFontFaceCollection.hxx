/* comment */
#pragma once

#include <sal/config.h>

#include <vcl/dllapi.h>

#include "PhysicalFontFace.hxx"

#include <vector>

/**
    A PhysicalFontFaceCollection is created by a PhysicalFontCollection and
    becomes invalid when original PhysicalFontCollection is modified.
 */

namespace vcl::font
{
class PhysicalFontFaceCollection
{
private:
    std::vector<rtl::Reference<PhysicalFontFace>> maDevFontVector;

public:
    PhysicalFontFaceCollection() { maDevFontVector.reserve(1024); }
    void Add(PhysicalFontFace* pFace) { maDevFontVector.push_back(pFace); }
    PhysicalFontFace* Get(int nIndex) const { return maDevFontVector[nIndex].get(); }
    int Count() const { return maDevFontVector.size(); }
};
}

/* comment */
