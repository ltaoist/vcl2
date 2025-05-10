/* comment */
#pragma once

#include <QtCore/QRectF>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

#include "QtFrame.hxx"
#include "QtGraphics.hxx"

class QtPainter final : public QPainter
{
    QtGraphicsBackend& m_rGraphics;
    QRegion m_aRegion;

public:
    QtPainter(QtGraphicsBackend& rGraphics, bool bPrepareBrush = false,
              sal_uInt8 nTransparency = 255);
    ~QtPainter();

    void update(int nx, int ny, int nw, int nh)
    {
        if (m_rGraphics.m_pFrame)
            m_aRegion += QRect(nx, ny, nw, nh);
    }

    void update(const QRect& rRect)
    {
        if (m_rGraphics.m_pFrame)
            m_aRegion += rRect;
    }

    void update(const QRectF& rRectF) { update(rRectF.toAlignedRect()); }

    void update()
    {
        if (m_rGraphics.m_pFrame)
            m_aRegion += m_rGraphics.m_pFrame->GetQWidget()->geometry();
    }
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
