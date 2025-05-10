/* comment */
#include <string.h>
#include <svsys.h>
#include <win/wincomp.hxx>
#include <win/saldata.hxx>
#include <win/salgdi.h>
#include <win/salbmp.h>

#include "gdiimpl.hxx"

bool WinSalGraphics::drawPolyPolygon(
    const basegfx::B2DHomMatrix& rObjectToDevice,
    const basegfx::B2DPolyPolygon& rPolyPolygon,
    double fTransparency)
{
    return mpImpl->drawPolyPolygon(
        rObjectToDevice,
        rPolyPolygon,
        fTransparency);
}

bool WinSalGraphics::drawPolyLine(
    const basegfx::B2DHomMatrix& rObjectToDevice,
    const basegfx::B2DPolygon& rPolygon,
    double fTransparency,
    double fLineWidth,
    const std::vector< double >* pStroke, // MM01
    basegfx::B2DLineJoin eLineJoin,
    css::drawing::LineCap eLineCap,
    double fMiterMinimumAngle,
    bool bPixelSnapHairline)
{
    return mpImpl->drawPolyLine(
        rObjectToDevice,
        rPolygon,
        fTransparency,
        fLineWidth,
        pStroke, // MM01
        eLineJoin,
        eLineCap,
        fMiterMinimumAngle,
        bPixelSnapHairline);
}

bool WinSalGraphics::blendBitmap(
    const SalTwoRect& rTR,
    const SalBitmap& rBmp)
{
    return mpImpl->blendBitmap(rTR, rBmp);
}

bool WinSalGraphics::blendAlphaBitmap(
    const SalTwoRect& rTR,
    const SalBitmap& rSrcBmp,
    const SalBitmap& rMaskBmp,
    const SalBitmap& rAlphaBmp)
{
    return mpImpl->blendAlphaBitmap(rTR, rSrcBmp, rMaskBmp, rAlphaBmp);
}

bool WinSalGraphics::drawAlphaBitmap(
    const SalTwoRect& rTR,
    const SalBitmap& rSrcBitmap,
    const SalBitmap& rAlphaBmp)
{
    return mpImpl->drawAlphaBitmap(rTR, rSrcBitmap, rAlphaBmp);
}

bool WinSalGraphics::drawTransformedBitmap(
    const basegfx::B2DPoint& rNull,
    const basegfx::B2DPoint& rX,
    const basegfx::B2DPoint& rY,
    const SalBitmap& rSourceBitmap,
    const SalBitmap* pAlphaBitmap,
    double fAlpha)
{
    return mpImpl->drawTransformedBitmap(rNull, rX, rY,
            rSourceBitmap, pAlphaBitmap, fAlpha);
}

bool WinSalGraphics::hasFastDrawTransformedBitmap() const
{
    return mpImpl->hasFastDrawTransformedBitmap();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
