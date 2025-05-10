/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALTIMER_H
#define INCLUDED_VCL_INC_OSX_SALTIMER_H

#include <premac.h>
#include <Cocoa/Cocoa.h>
#include <postmac.h>

#include <saltimer.hxx>

/**
 * if NO == bAtStart, then it has to be run in the main thread,
 * e.g. via performSelectorOnMainThread!
 **/
void ImplNSAppPostEvent( short nEventId, BOOL bAtStart, int nUserData = 0 );

class ReleasePoolHolder
{
    NSAutoreleasePool* mpPool;

public:
    ReleasePoolHolder() : mpPool( [[NSAutoreleasePool alloc] init] ) {}
    ~ReleasePoolHolder() { [mpPool release]; }
};

class AquaSalTimer final : public SalTimer, protected VersionedEvent
{
    NSTimer    *m_pRunningTimer;
    bool        m_bDirectTimeout;    ///< timeout can be processed directly

    void queueDispatchTimerEvent( bool bAtStart );
    void callTimerCallback();

public:
    AquaSalTimer();
    virtual ~AquaSalTimer() override;

    void Start( sal_uInt64 nMS ) override;
    void Stop() override;

    void handleStartTimerEvent( NSEvent* pEvent );
    bool handleDispatchTimerEvent( NSEvent* pEvent );
    void handleTimerElapsed();
    void handleWindowShouldClose();

    bool IsTimerElapsed() const;
    inline bool IsDirectTimeout() const;
};

inline bool AquaSalTimer::IsDirectTimeout() const
{
    return m_bDirectTimeout;
}

#endif // INCLUDED_VCL_INC_OSX_SALTIMER_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
