/* comment */
#ifndef INCLUDED_VCL_INC_UNX_FC_FONTOPTIONS_HXX
#define INCLUDED_VCL_INC_UNX_FC_FONTOPTIONS_HXX

#include <rtl/string.hxx>

typedef struct _FcPattern   FcPattern;
class VCL_DLLPUBLIC FontConfigFontOptions
{
public:
                        FontConfigFontOptions(FcPattern* pPattern) :
                            mpPattern(pPattern) {}
                        ~FontConfigFontOptions();

    void                SyncPattern(const OString& rFileName, sal_uInt32 nFontFace, sal_uInt32 nFontVariation, bool bEmbolden);
    FcPattern*          GetPattern() const;
    static void         cairo_font_options_substitute(FcPattern* pPattern);
private:
    FcPattern* mpPattern;
};


#endif // INCLUDED_VCL_INC_UNX_FC_FONTOPTIONS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
