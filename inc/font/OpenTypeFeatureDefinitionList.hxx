/* comment */

#pragma once

#include <vcl/dllapi.h>
#include <vcl/font/Feature.hxx>
#include <vector>
#include <unordered_map>

namespace vcl::font
{
class OpenTypeFeatureDefinitionListPrivate
{
private:
    std::vector<FeatureDefinition> m_aFeatureDefinition;
    std::unordered_map<sal_uInt32, size_t> m_aCodeToIndex;
    std::vector<sal_uInt32> m_aRequiredFeatures;

    void init();

    static bool isSpecialFeatureCode(sal_uInt32 nFeatureCode);
    static FeatureDefinition handleSpecialFeatureCode(sal_uInt32 nFeatureCode);

public:
    OpenTypeFeatureDefinitionListPrivate();
    FeatureDefinition getDefinition(sal_uInt32 nFeatureCode);
    bool isRequired(sal_uInt32 nFeatureCode);
};

VCL_DLLPUBLIC OpenTypeFeatureDefinitionListPrivate& OpenTypeFeatureDefinitionList();

} // namespace vcl::font

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
