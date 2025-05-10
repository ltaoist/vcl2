/* comment */
#pragma once

#include <vcl/toolkit/floatwin.hxx>
#include <vcl/image.hxx>
#include <vcl/menu.hxx>

class BubbleWindow final : public FloatingWindow
{
    Point           maTipPos;
    vcl::Region     maBounds;
    tools::Polygon  maRectPoly;
    tools::Polygon  maTriPoly;
    OUString        maBubbleTitle;
    OUString        maBubbleText;
    Image           maBubbleImage;
    Size            maMaxTextSize;
    tools::Rectangle       maTitleRect;
    tools::Rectangle       maTextRect;
    tools::Long     mnTipOffset;

private:
    void            RecalcTextRects();

public:
                    BubbleWindow( vcl::Window* pParent, OUString aTitle,
                                  OUString aText, Image aImage );

    virtual void    MouseButtonDown( const MouseEvent& rMEvt ) override;
    virtual void    Paint(vcl::RenderContext& rRenderContext, const tools::Rectangle& rRect) override;
    void            Resize() override;
    void            Show( bool bVisible = true );
    void            SetTipPosPixel( const Point& rTipPos ) { maTipPos = rTipPos; }
    void            SetTitleAndText( const OUString& rTitle, const OUString& rText,
                                     const Image& rImage );
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
