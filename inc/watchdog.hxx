/* comment */

#ifndef INCLUDED_VCL_INC_WATCHDOG_H
#define INCLUDED_VCL_INC_WATCHDOG_H

#include <sal/config.h>
#include <salhelper/thread.hxx>
#include <atomic>
#include <vector>

class WatchdogThread final : private salhelper::Thread
{
    WatchdogThread();
    virtual void execute() override;

public:
    using salhelper::Thread::acquire;
    using salhelper::Thread::release;
    static void start();
    static void stop();
};

#endif // INCLUDED_VCL_INC_WATCHDOG_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
