/* comment */
#pragma once

#include <saltimer.hxx>
#include <QtCore/QTimer>

class QtTimer final : public QObject, public SalTimer
{
    Q_OBJECT

    QTimer m_aTimer;

private Q_SLOTS:
    void timeoutActivated();
    void startTimer(int);
    void stopTimer();

Q_SIGNALS:
    void startTimerSignal(int);
    void stopTimerSignal();

public:
    QtTimer();

    int remainingTime() const { return m_aTimer.remainingTime(); }

    virtual void Start(sal_uInt64 nMS) override;
    virtual void Stop() override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
