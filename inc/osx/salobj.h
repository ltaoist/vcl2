/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALOBJ_H
#define INCLUDED_VCL_INC_OSX_SALOBJ_H

#include <sal/config.h>

#include <tools/long.hxx>
#include <vcl/sysdata.hxx>
#include <salobj.hxx>

class AquaSalFrame;
class AquaSalObject;


struct SalObjectData
{
};

class AquaSalObject : public SalObject
{
public:
    AquaSalFrame*               mpFrame;                // parent frame
    NSClipView*                 mpClipView;
    SystemEnvData               maSysData;

    CGFloat                     mnClipX;
    CGFloat                     mnClipY;
    CGFloat                     mnClipWidth;
    CGFloat                     mnClipHeight;
    bool                        mbClip;

    CGFloat                     mnX;
    CGFloat                     mnY;
    CGFloat                     mnWidth;
    CGFloat                     mnHeight;

    void setClippedPosSize();

    AquaSalObject( AquaSalFrame* pFrame, SystemWindowData const * pWinData );
    virtual ~AquaSalObject() override;

    virtual void                    ResetClipRegion() override;
    virtual void                    BeginSetClipRegion( sal_uInt32 nRects ) override;
    virtual void                    UnionClipRegion( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    EndSetClipRegion() override;
    virtual void                    SetPosSize( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    Show( bool bVisible ) override;
    virtual const SystemEnvData*    GetSystemData() const override;
};

#endif // INCLUDED_VCL_INC_OSX_SALOBJ_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
