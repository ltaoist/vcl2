/* comment */
#pragma once

#include <vcl/dllapi.h>
#include <vcl/animate/Animation.hxx>
#include <vcl/vclptr.hxx>

class Animation;
class OutputDevice;
class VirtualDevice;
struct AnimationFrame;

struct AnimationData
{
    Point maOriginStartPt;
    Size maStartSize;
    VclPtr<OutputDevice> mpRenderContext;
    void* mpRendererData;
    tools::Long mnRendererId;
    bool mbIsPaused;

    AnimationData();
};


class VCL_DLLPUBLIC AnimationRenderer
{
private:
    Animation*      mpParent;
    VclPtr<OutputDevice>  mpRenderContext;
    tools::Long     mnRendererId;
    Point           maOriginPt;
    Point           maDispPt;
    Point           maRestPt;
    Size            maLogicalSize;
    Size            maSizePx;
    Size            maDispSz;
    Size            maRestSz;
    vcl::Region     maClip;
    VclPtr<VirtualDevice>  mpBackground;
    VclPtr<VirtualDevice>  mpRestore;
    sal_uLong       mnActIndex;
    Disposal        meLastDisposal;
    bool            mbIsPaused;
    bool            mbIsMarked;
    bool            mbIsMirroredHorizontally;
    bool            mbIsMirroredVertically;

public:
                    AnimationRenderer( Animation* pParent, OutputDevice* pOut,
                                  const Point& rPt, const Size& rSz, sal_uLong nRendererId,
                                  OutputDevice* pFirstFrameOutDev = nullptr );
                    AnimationRenderer(AnimationRenderer&&) = delete;
                    ~AnimationRenderer();

    bool            matches(const OutputDevice* pOut, tools::Long nRendererId) const;
    void            drawToIndex( sal_uLong nIndex );
    void            draw( sal_uLong nIndex, VirtualDevice* pVDev=nullptr );
    void            repaint();
    AnimationData*  createAnimationData() const;

    void            getPosSize( const AnimationFrame& rAnm, Point& rPosPix, Size& rSizePix );

    const Point&    getOriginPosition() const { return maOriginPt; }

    const Size&     getOutSizePix() const { return maSizePx; }

    void            pause( bool bIsPaused ) { mbIsPaused = bIsPaused; }
    bool            isPaused() const { return mbIsPaused; }

    void            setMarked( bool bIsMarked ) { mbIsMarked = bIsMarked; }
    bool            isMarked() const { return mbIsMarked; }
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
