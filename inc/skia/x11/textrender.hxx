/* comment */
#ifndef INCLUDED_VCL_INC_SKIA_TEXTRENDER_HXX
#define INCLUDED_VCL_INC_SKIA_TEXTRENDER_HXX

#include <unx/freetypetextrender.hxx>

#include <SkFontMgr.h>
#include <SkFontMgr_fontconfig.h>

class VCL_DLLPUBLIC SkiaTextRender final : public FreeTypeTextRenderImpl
{
public:
    virtual void DrawTextLayout(const GenericSalLayout&, const SalGraphics&) override;
    virtual void ClearDevFontCache() override;

private:
    static inline sk_sp<SkFontMgr> fontManager;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
