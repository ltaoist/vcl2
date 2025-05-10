/* comment */
#pragma once

#include <vcl/outdev.hxx>

namespace vcl
{
class WindowOutputDevice final : public ::OutputDevice
{
public:
    WindowOutputDevice(vcl::Window& rOwnerWindow);
    virtual ~WindowOutputDevice() override;
    virtual void dispose() override;

    size_t GetSyncCount() const override { return 0x000000ff; }
    virtual void EnableRTL(bool bEnable = true) override;

    void Flush() override;

    void SaveBackground(VirtualDevice& rSaveDevice, const Point& rPos, const Size& rSize,
                        const Size&) const override;

    css::awt::DeviceInfo GetDeviceInfo() const override;

    virtual vcl::Region GetActiveClipRegion() const override;
    virtual vcl::Region GetOutputBoundsClipRegion() const override;

    virtual bool AcquireGraphics() const override;
    virtual void ReleaseGraphics(bool bRelease = true) override;

    Color GetBackgroundColor() const override;

    using ::OutputDevice::SetSettings;
    virtual void SetSettings(const AllSettings& rSettings) override;
    void SetSettings(const AllSettings& rSettings, bool bChild);

    bool CanEnableNativeWidget() const override;

    /** Get the vcl::Window that this OutputDevice belongs to, if any */
    virtual vcl::Window* GetOwnerWindow() const override { return mxOwnerWindow.get(); }

    virtual css::uno::Reference<css::rendering::XCanvas>
    ImplGetCanvas(bool bSpriteCanvas) const override;

private:
    virtual void InitClipRegion() override;

    void ImplClearFontData(bool bNewFontLists) override;
    void ImplRefreshFontData(bool bNewFontLists) override;
    void ImplInitMapModeObjects() override;

    virtual void CopyDeviceArea(SalTwoRect& aPosAry, bool bWindowInvalidate) override;
    virtual const OutputDevice* DrawOutDevDirectCheck(const OutputDevice& rSrcDev) const override;
    virtual void DrawOutDevDirectProcess(const OutputDevice& rSrcDev, SalTwoRect& rPosAry,
                                         SalGraphics* pSrcGraphics) override;
    virtual void ClipToPaintRegion(tools::Rectangle& rDstRect) override;
    virtual bool UsePolyPolygonForComplexGradient() override;

    VclPtr<vcl::Window> mxOwnerWindow;
};

}; // namespace vcl

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
