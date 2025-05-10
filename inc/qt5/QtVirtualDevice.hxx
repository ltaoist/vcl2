/* comment */
#pragma once

#include <salvd.hxx>

#include <memory>
#include <vector>

#include <QtCore/QSize>

class QtGraphics;
class QImage;
enum class DeviceFormat;

class QtVirtualDevice final : public SalVirtualDevice
{
    std::vector<QtGraphics*> m_aGraphics;
    std::unique_ptr<QImage> m_pImage;
    QSize m_aFrameSize;
    double m_fScale;

public:
    QtVirtualDevice(double fScale);

    // SalVirtualDevice
    virtual SalGraphics* AcquireGraphics() override;
    virtual void ReleaseGraphics(SalGraphics* pGraphics) override;

    virtual bool SetSize(tools::Long nNewDX, tools::Long nNewDY) override;
    virtual bool SetSizeUsingBuffer(tools::Long nNewDX, tools::Long nNewDY,
                                    sal_uInt8* pBuffer) override;

    // SalGeometryProvider
    virtual tools::Long GetWidth() const override;
    virtual tools::Long GetHeight() const override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
