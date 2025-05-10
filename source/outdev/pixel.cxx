/* comment */
#include <cassert>

#include <vcl/gdimtf.hxx>
#include <vcl/metaact.hxx>
#include <vcl/outdev.hxx>
#include <vcl/virdev.hxx>

#include <drawmode.hxx>
#include <salgdi.hxx>

Color OutputDevice::GetPixel(const Point& rPoint) const
{
    Color aColor;

    if (mpGraphics || AcquireGraphics())
    {
        assert(mpGraphics);
        if (mbInitClipRegion)
            const_cast<OutputDevice*>(this)->InitClipRegion();

        if (!mbOutputClipped)
        {
            const tools::Long nX = ImplLogicXToDevicePixel(rPoint.X());
            const tools::Long nY = ImplLogicYToDevicePixel(rPoint.Y());
            aColor = mpGraphics->GetPixel(nX, nY, *this);

            if (mpAlphaVDev)
            {
                Color aAlphaColor = mpAlphaVDev->GetPixel(rPoint);
                aColor.SetAlpha(255 - aAlphaColor.GetBlue());
            }
        }
    }
    return aColor;
}

void OutputDevice::DrawPixel( const Point& rPt )
{
    assert(!is_double_buffered_window());

    if ( mpMetaFile )
        mpMetaFile->AddAction( new MetaPointAction( rPt ) );

    if ( !IsDeviceOutputNecessary() || !mbLineColor || ImplIsRecordLayout() )
        return;

    Point aPt = ImplLogicToDevicePixel( rPt );

    if ( !mpGraphics && !AcquireGraphics() )
        return;
    assert(mpGraphics);

    if ( mbInitClipRegion )
        InitClipRegion();

    if ( mbOutputClipped )
        return;

    if ( mbInitLineColor )
        InitLineColor();

    mpGraphics->DrawPixel( aPt.X(), aPt.Y(), *this );

    if( mpAlphaVDev )
        mpAlphaVDev->DrawPixel( rPt );
}

void OutputDevice::DrawPixel( const Point& rPt, const Color& rColor )
{
    assert(!is_double_buffered_window());

    Color aColor = vcl::drawmode::GetLineColor(rColor, GetDrawMode(), GetSettings().GetStyleSettings());

    if ( mpMetaFile )
        mpMetaFile->AddAction( new MetaPixelAction( rPt, aColor ) );

    if ( !IsDeviceOutputNecessary() || ImplIsRecordLayout() )
        return;

    Point aPt = ImplLogicToDevicePixel( rPt );

    if ( !mpGraphics && !AcquireGraphics() )
        return;
    assert(mpGraphics);

    if ( mbInitClipRegion )
        InitClipRegion();

    if ( mbOutputClipped )
        return;

    mpGraphics->DrawPixel( aPt.X(), aPt.Y(), aColor, *this );

    if (mpAlphaVDev)
    {
        Color aAlphaColor(255 - rColor.GetAlpha(), 255 - rColor.GetAlpha(), 255 - rColor.GetAlpha());
        mpAlphaVDev->DrawPixel(rPt, aAlphaColor);
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
