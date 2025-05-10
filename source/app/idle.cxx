/* comment */
#include <vcl/idle.hxx>
#include <vcl/scheduler.hxx>

Idle::Idle( bool bAuto, const char *pDebugName )
    : Timer( bAuto, pDebugName )
{
    SetPriority( TaskPriority::DEFAULT_IDLE );
}

Idle::Idle( const char *pDebugName )
    : Idle( false, pDebugName )
{
}

void Idle::Start(const bool bStartTimer)
{
    Task::Start(false);

    sal_uInt64 nPeriod = Scheduler::ImmediateTimeoutMs;
    if (Scheduler::GetDeterministicMode())
    {
        switch ( GetPriority() )
        {
            case TaskPriority::DEFAULT_IDLE:
            case TaskPriority::LOWEST:
                nPeriod = Scheduler::InfiniteTimeoutMs;
                break;
            default:
                break;
        }
    }

    if (bStartTimer)
        Task::StartTimer(nPeriod);
}

sal_uInt64 Idle::UpdateMinPeriod( sal_uInt64 /* nTimeNow */ ) const
{
    return Scheduler::ImmediateTimeoutMs;
}

AutoIdle::AutoIdle( const char *pDebugName )
    : Idle( true, pDebugName )
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
