/* comment */
#include <vcl/BitmapInfoAccess.hxx>

#include <salbmp.hxx>
#include <svdata.hxx>
#include <salinst.hxx>

BitmapInfoAccess::BitmapInfoAccess(Bitmap& rBitmap, BitmapAccessMode nMode)
    : mpBuffer(nullptr)
    , mnAccessMode(nMode)
{
    std::shared_ptr<SalBitmap> xImpBmp = rBitmap.ImplGetSalBitmap();

    if (!xImpBmp)
        return;

    if (mnAccessMode == BitmapAccessMode::Write)
    {
        xImpBmp->DropScaledCache();

        if (xImpBmp.use_count() > 2)
        {
            xImpBmp.reset();
            rBitmap.ImplMakeUnique();
            xImpBmp = rBitmap.ImplGetSalBitmap();
        }
    }

    mpBuffer = xImpBmp->AcquireBuffer(mnAccessMode);

    if (!mpBuffer)
    {
        std::shared_ptr<SalBitmap> xNewImpBmp(ImplGetSVData()->mpDefInst->CreateSalBitmap());
        if (xNewImpBmp->Create(*xImpBmp, rBitmap.getPixelFormat()))
        {
            xImpBmp = xNewImpBmp;
            rBitmap.ImplSetSalBitmap(xImpBmp);
            mpBuffer = xImpBmp->AcquireBuffer(mnAccessMode);
        }
    }

    maBitmap = rBitmap;
}

BitmapInfoAccess::~BitmapInfoAccess()
{
    std::shared_ptr<SalBitmap> xImpBmp = maBitmap.ImplGetSalBitmap();

    if (mpBuffer && xImpBmp)
    {
        xImpBmp->ReleaseBuffer(mpBuffer, mnAccessMode);
    }
}

sal_uInt16 BitmapInfoAccess::GetBestPaletteIndex(const BitmapColor& rBitmapColor) const
{
    const BitmapBuffer* pBuffer = mpBuffer;

    return (HasPalette() ? pBuffer->maPalette.GetBestIndex(rBitmapColor) : 0);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
