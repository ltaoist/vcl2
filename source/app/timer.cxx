/* comment */
#include <sal/log.hxx>
#include <vcl/timer.hxx>
#include <vcl/scheduler.hxx>
#include <schedulerimpl.hxx>

void Timer::SetDeletionFlags()
{
    // If no AutoTimer, then stop.
    if ( !mbAuto )
        Task::SetDeletionFlags();
}

sal_uInt64 Timer::UpdateMinPeriod( sal_uInt64 nTimeNow ) const
{
    sal_uInt64 nWakeupTime = GetSchedulerData()->mnUpdateTime + mnTimeout;
    return ( nWakeupTime <= nTimeNow )
        ? Scheduler::ImmediateTimeoutMs : nWakeupTime - nTimeNow;
}

Timer::Timer( bool bAuto, const char *pDebugName )
    : Task( pDebugName )
    , mnTimeout( Scheduler::ImmediateTimeoutMs )
    , mbAuto( bAuto )
{
    SetPriority( TaskPriority::DEFAULT );
}

Timer::Timer( const char *pDebugName )
    : Timer( false, pDebugName )
{
}

Timer::Timer( const Timer& rTimer )
    : Timer( rTimer.mbAuto, rTimer.GetDebugName() )
{
    maInvokeHandler = rTimer.maInvokeHandler;
    mnTimeout = rTimer.mnTimeout;
}

Timer::~Timer()
{
}

Timer& Timer::operator=( const Timer& rTimer )
{
    Task::operator=( rTimer );
    maInvokeHandler = rTimer.maInvokeHandler;
    mnTimeout = rTimer.mnTimeout;
    SAL_WARN_IF( mbAuto != rTimer.mbAuto, "vcl.schedule",
        "Copying Timer with different mbAuto value!" );
    return *this;
}

void Timer::Invoke()
{
    maInvokeHandler.Call( this );
}

void Timer::Invoke( Timer *arg )
{
    maInvokeHandler.Call( arg );
}

void Timer::Start(const bool bStartTimer)
{
    Task::Start(false);
    if (bStartTimer)
        Task::StartTimer(mnTimeout);
}

void Timer::SetTimeout( sal_uInt64 nNewTimeout )
{
    mnTimeout = nNewTimeout;
    // If timer is active, then renew clock.
    if ( IsActive() )
        StartTimer( mnTimeout );
}

AutoTimer::AutoTimer( const char *pDebugName )
    : Timer( true, pDebugName )
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
