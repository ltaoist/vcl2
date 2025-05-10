/* comment */
#ifndef INCLUDED_VCL_INC_IMPFONTCHARMAP_HXX
#define INCLUDED_VCL_INC_IMPFONTCHARMAP_HXX

#include <tools/ref.hxx>
#include <vcl/dllapi.h>
#include <vector>

class ImplFontCharMap;
typedef tools::SvRef<ImplFontCharMap> ImplFontCharMapRef;

class ImplFontCharMap final : public SvRefBase
{
public:
    explicit            ImplFontCharMap( bool bSymbolic,
                                         std::vector<sal_uInt32> aRangeCodes);
    virtual             ~ImplFontCharMap() override;

private:
    friend class FontCharMap;

                        ImplFontCharMap( const ImplFontCharMap& ) = delete;
    void                operator=( const ImplFontCharMap& ) = delete;

    static ImplFontCharMapRef const & getDefaultMap( bool bSymbols=false);
    bool                isDefaultMap() const;

private:
    std::vector<sal_uInt32> maRangeCodes; // pairs of StartCode/(EndCode+1)
    int                 mnCharCount;      // covered codepoints
    const bool m_bSymbolic;
};

bool VCL_DLLPUBLIC HasSymbolCmap(const unsigned char* pRawData, int nRawLength);

#endif // INCLUDED_VCL_INC_IMPFONTCHARMAP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
