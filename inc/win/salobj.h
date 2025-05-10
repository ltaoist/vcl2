/* comment */
#ifndef INCLUDED_VCL_INC_WIN_SALOBJ_H
#define INCLUDED_VCL_INC_WIN_SALOBJ_H

#include <salobj.hxx>


class WinSalObject : public SalObject
{
public:
    HWND                    mhWnd;                  // Window handle
    HWND                    mhWndChild;             // Child Window handle
    HWND                    mhLastFocusWnd;         // Child-Window, which had the last focus
    SystemEnvData           maSysData;              // SystemEnvData
    RGNDATA*                mpClipRgnData;          // ClipRegion-Data
    RGNDATA*                mpStdClipRgnData;       // Cache Standard-ClipRegion-Data
    RECT*                   mpNextClipRect;         // next ClipRegion-Rect
    bool                    mbFirstClipRect;        // Flag for first cliprect to insert
    WinSalObject*           mpNextObject;           // pointer to next object

    WinSalObject();
    virtual ~WinSalObject() override;

    virtual void                    ResetClipRegion() override;
    virtual void                    BeginSetClipRegion( sal_uInt32 nRects ) override;
    virtual void                    UnionClipRegion( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight) override;
    virtual void                    EndSetClipRegion() override;
    virtual void                    SetPosSize( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    Show( bool bVisible ) override;
    virtual void                    Enable( bool bEnable ) override;
    virtual void                    GrabFocus() override;
    virtual const SystemEnvData*    GetSystemData() const override;
};

#endif // INCLUDED_VCL_INC_WIN_SALOBJ_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
