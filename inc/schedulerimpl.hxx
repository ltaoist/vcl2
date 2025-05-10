/* comment */
#ifndef INCLUDED_VCL_INC_SCHEDULERIMPL_HXX
#define INCLUDED_VCL_INC_SCHEDULERIMPL_HXX

#include "salwtype.hxx"
#include <vcl/scheduler.hxx>

class Task;

// Internal scheduler record holding intrusive linked list pieces
struct ImplSchedulerData final
{
    ImplSchedulerData* mpNext;        ///< Pointer to the next element in list
    Task*              mpTask;        ///< Pointer to VCL Task instance
    sal_uInt64         mnUpdateTime;  ///< Last Update Time
    TaskPriority       mePriority;    ///< Task priority
    /**
     * Is the Task currently processed / on the stack?
     *
     * Since the introduction of the scheduler stack, this became merely a
     * debugging and assertion hint. No decisions are anymore made based on
     * this, because invoked Tasks are removed from the scheduler lists and
     * placed on the stack, so no code should actually ever find one, where
     * mbInScheduler is true (I don't see a reason to walk the stack for
     * normal Scheduler usage, that is).
     *
     * This was originally used to prevent invoking Tasks recursively.
     **/
    bool               mbInScheduler; ///< Task currently processed?

    const char *GetDebugName() const;
};

class SchedulerGuard final
{
public:
    SchedulerGuard()
    {
        Scheduler::Lock();
    }

    ~SchedulerGuard()
    {
        Scheduler::Unlock();
    }
};

#endif // INCLUDED_VCL_INC_SCHEDULERIMPL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
