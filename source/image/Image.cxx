/* comment */
#include <vcl/settings.hxx>
#include <vcl/outdev.hxx>
#include <vcl/graph.hxx>
#include <vcl/graphicfilter.hxx>
#include <vcl/image.hxx>
#include <sal/types.h>
#include <image.h>

#include <bitmap/BitmapColorizeFilter.hxx>

using namespace css;

Image::Image()
{
}

Image::Image(const BitmapEx& rBitmapEx)
{
    ImplInit(rBitmapEx);
}

Image::Image(uno::Reference<graphic::XGraphic> const & rxGraphic)
{
    if (rxGraphic.is())
    {
        const Graphic aGraphic(rxGraphic);

        OUString aPath;
        if (aGraphic.getOriginURL().startsWith("private:graphicrepository/", &aPath))
            mpImplData = std::make_shared<ImplImage>(aPath);
        else
            ImplInit(aGraphic.GetBitmapEx());
    }
}

Image::Image(const OUString & rFileUrl)
{
    OUString sImageName;
    if (rFileUrl.startsWith("private:graphicrepository/", &sImageName))
        mpImplData = std::make_shared<ImplImage>(sImageName);
    else
    {
        Graphic aGraphic;
        if (ERRCODE_NONE == GraphicFilter::LoadGraphic(rFileUrl, IMP_PNG, aGraphic))
            ImplInit(aGraphic.GetBitmapEx());
    }
}

Image::Image(StockImage, const OUString & rFileUrl)
    : mpImplData(std::make_shared<ImplImage>(rFileUrl))
{
}

void Image::ImplInit(const BitmapEx& rBitmapEx)
{
    if (!rBitmapEx.IsEmpty())
        mpImplData = std::make_shared<ImplImage>(rBitmapEx);
}

OUString Image::GetStock() const
{
    if (mpImplData)
        return mpImplData->getStock();
    return OUString();
}

Size Image::GetSizePixel() const
{
    if (mpImplData)
        return mpImplData->getSizePixel();
    else
        return Size();
}

BitmapEx Image::GetBitmapEx() const
{
    if (mpImplData)
        return mpImplData->getBitmapEx();
    else
        return BitmapEx();
}

bool Image::operator==(const Image& rImage) const
{
    bool bRet = false;

    if (rImage.mpImplData == mpImplData)
        bRet = true;
    else if (!rImage.mpImplData || !mpImplData)
        bRet = false;
    else
        bRet = rImage.mpImplData->isEqual(*mpImplData);

    return bRet;
}

void Image::Draw(OutputDevice* pOutDev, const Point& rPos, DrawImageFlags nStyle, const Size* pSize)
{
    if (!mpImplData || (!pOutDev->IsDeviceOutputNecessary() && pOutDev->GetConnectMetaFile() == nullptr))
        return;

    Size aOutSize = pSize ? *pSize : pOutDev->PixelToLogic(mpImplData->getSizePixel());

    BitmapEx aRenderBmp = mpImplData->getBitmapExForHiDPI(bool(nStyle & DrawImageFlags::Disable), pOutDev->GetGraphics());

    if (!(nStyle & DrawImageFlags::Disable) &&
        (nStyle & (DrawImageFlags::ColorTransform | DrawImageFlags::Highlight |
                   DrawImageFlags::Deactive | DrawImageFlags::SemiTransparent)))
    {
        BitmapEx aTempBitmapEx(aRenderBmp);

        if (nStyle & (DrawImageFlags::Highlight | DrawImageFlags::Deactive))
        {
            const StyleSettings& rSettings = pOutDev->GetSettings().GetStyleSettings();
            Color aColor;
            if (nStyle & DrawImageFlags::Highlight)
                aColor = rSettings.GetHighlightColor();
            else
                aColor = rSettings.GetDeactiveColor();

            BitmapFilter::Filter(aTempBitmapEx, BitmapColorizeFilter(aColor));
        }

        if (nStyle & DrawImageFlags::SemiTransparent)
        {
            if (aTempBitmapEx.IsAlpha())
            {
                Bitmap aAlphaBmp(aTempBitmapEx.GetAlpha().GetBitmap());
                aAlphaBmp.Adjust(50);
                aTempBitmapEx = BitmapEx(aTempBitmapEx.GetBitmap(), AlphaMask(aAlphaBmp));
            }
            else
            {
                sal_uInt8 cErase = 128;
                aTempBitmapEx = BitmapEx(aTempBitmapEx.GetBitmap(), AlphaMask(aTempBitmapEx.GetSizePixel(), &cErase));
            }
        }
        aRenderBmp = aTempBitmapEx;
    }

    pOutDev->DrawBitmapEx(rPos, aOutSize, aRenderBmp);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
