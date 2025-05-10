/* comment */
#include <QtVirtualDevice.hxx>

#include <QtGraphics.hxx>
#include <QtTools.hxx>

#include <QtGui/QImage>

QtVirtualDevice::QtVirtualDevice(double fScale)
    : m_fScale(fScale)
{
}

SalGraphics* QtVirtualDevice::AcquireGraphics()
{
    assert(m_pImage);
    QtGraphics* pGraphics = new QtGraphics(m_pImage.get());
    m_aGraphics.push_back(pGraphics);
    return pGraphics;
}

void QtVirtualDevice::ReleaseGraphics(SalGraphics* pGraphics)
{
    m_aGraphics.erase(
        std::remove(m_aGraphics.begin(), m_aGraphics.end(), dynamic_cast<QtGraphics*>(pGraphics)),
        m_aGraphics.end());
    delete pGraphics;
}

bool QtVirtualDevice::SetSize(tools::Long nNewDX, tools::Long nNewDY)
{
    return SetSizeUsingBuffer(nNewDX, nNewDY, nullptr);
}

bool QtVirtualDevice::SetSizeUsingBuffer(tools::Long nNewDX, tools::Long nNewDY, sal_uInt8* pBuffer)
{
    if (nNewDX == 0)
        nNewDX = 1;
    if (nNewDY == 0)
        nNewDY = 1;

    if (m_pImage && m_aFrameSize.width() == nNewDX && m_aFrameSize.height() == nNewDY)
        return true;

    m_aFrameSize = QSize(nNewDX, nNewDY);

    nNewDX *= m_fScale;
    nNewDY *= m_fScale;

    if (pBuffer)
        m_pImage.reset(new QImage(pBuffer, nNewDX, nNewDY, Qt_DefaultFormat32));
    else
        m_pImage.reset(new QImage(nNewDX, nNewDY, Qt_DefaultFormat32));

    m_pImage->fill(Qt::transparent);
    m_pImage->setDevicePixelRatio(m_fScale);

    // update device in existing graphics
    for (auto pQtGraph : m_aGraphics)
        pQtGraph->ChangeQImage(m_pImage.get());

    return true;
}

tools::Long QtVirtualDevice::GetWidth() const { return m_pImage ? m_aFrameSize.width() : 0; }

tools::Long QtVirtualDevice::GetHeight() const { return m_pImage ? m_aFrameSize.height() : 0; }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
