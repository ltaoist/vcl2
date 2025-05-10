/* comment */
#include <QtTimer.hxx>
#include <QtTimer.moc>

#include <QtInstance.hxx>

#include <QtWidgets/QApplication>
#include <QtCore/QThread>

#include <vcl/svapp.hxx>
#include <sal/log.hxx>

#include <svdata.hxx>

QtTimer::QtTimer()
{
    m_aTimer.setSingleShot(true);
    m_aTimer.setTimerType(Qt::PreciseTimer);
    connect(&m_aTimer, SIGNAL(timeout()), this, SLOT(timeoutActivated()));
    connect(this, SIGNAL(startTimerSignal(int)), this, SLOT(startTimer(int)));
    connect(this, SIGNAL(stopTimerSignal()), this, SLOT(stopTimer()));
}

void QtTimer::timeoutActivated()
{
    SolarMutexGuard aGuard;
    if (Application::IsOnSystemEventLoop())
    {
        const ImplSVData* pSVData = ImplGetSVData();
        assert(pSVData && pSVData->mpDefInst);
        static_cast<QtInstance*>(pSVData->mpDefInst)->DispatchUserEvents(true);
    }
    CallCallback();
}

void QtTimer::startTimer(int nMS) { m_aTimer.start(nMS); }

void QtTimer::Start(sal_uInt64 nMS) { Q_EMIT startTimerSignal(nMS); }

void QtTimer::stopTimer() { m_aTimer.stop(); }

void QtTimer::Stop() { Q_EMIT stopTimerSignal(); }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
