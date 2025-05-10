/* comment */

#pragma once

#include <QtWidgets/QApplication>

class QtGraphicsBase
{
    qreal m_fDPR;

public:
    QtGraphicsBase()
        : m_fDPR(qApp ? qApp->devicePixelRatio() : 1.0)
    {
    }

    void setDevicePixelRatioF(qreal fDPR) { m_fDPR = fDPR; }

    qreal devicePixelRatioF() const { return m_fDPR; }
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
