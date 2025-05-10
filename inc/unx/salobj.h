/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALOBJ_H
#define INCLUDED_VCL_INC_UNX_SALOBJ_H

#include <X11/Xlib.h>

#include <salobj.hxx>
#include <vcl/sysdata.hxx>
#include <vclpluginapi.h>
#include <memory>

class SalClipRegion
{

public:

                SalClipRegion();
               ~SalClipRegion();

    void        BeginSetClipRegion( sal_uInt32 nRects );
    void        UnionClipRegion( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight );

    XRectangle *EndSetClipRegion()  {
        return ClipRectangleList.get(); }
    void        ResetClipRegion()   {
        numClipRectangles = 0;      }
    int         GetRectangleCount() const {
        return numClipRectangles;   }

private:

    std::unique_ptr<XRectangle[]>
                ClipRectangleList;
    int         numClipRectangles;
    int         maxClipRectangles;
};

class X11SalObject final : public SalObject
{
public:
    SystemEnvData maSystemChildData;
    SalFrame*       mpParent;
    ::Window        maParentWin;
    ::Window        maPrimary;
    ::Window        maSecondary;
    Colormap        maColormap;
    SalClipRegion   maClipRegion;
    bool            mbVisible;

    static VCL_DLLPUBLIC bool Dispatch( XEvent* pEvent );
    static VCL_DLLPUBLIC X11SalObject* CreateObject( SalFrame* pParent, SystemWindowData* pWindowData, bool bShow );

    X11SalObject();
    virtual ~X11SalObject() override;

    // override all pure virtual methods
    virtual void                    ResetClipRegion() override;
    virtual void                    BeginSetClipRegion( sal_uInt32 nRects ) override;
    virtual void                    UnionClipRegion( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    EndSetClipRegion() override;

    virtual void                    SetPosSize( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    Show( bool bVisible ) override;
    virtual void                    GrabFocus() override;

    virtual void                    SetLeaveEnterBackgrounds(const css::uno::Sequence<css::uno::Any>& rLeaveArgs, const css::uno::Sequence<css::uno::Any>& rEnterArgs) override;

    virtual const SystemEnvData*    GetSystemData() const override;
};

#endif // INCLUDED_VCL_INC_UNX_SALOBJ_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
