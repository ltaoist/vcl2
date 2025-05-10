/* comment */
#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

#include "QtFrame.hxx"

class QtMainWindow final : public QMainWindow
{
    Q_OBJECT

    QtFrame& m_rFrame;

    virtual void closeEvent(QCloseEvent* pEvent) override;
    void moveEvent(QMoveEvent*) override;

public:
    QtMainWindow(QtFrame& rFrame, Qt::WindowFlags f = Qt::WindowFlags());
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
