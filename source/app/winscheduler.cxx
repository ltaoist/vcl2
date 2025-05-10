/* comment */
#ifdef _WIN32

#include <sal/config.h>

#include <sal/log.hxx>
#include <vcl/winscheduler.hxx>

#include <svsys.h>
#include <win/saldata.hxx>
#include <win/salinst.h>

namespace
{
void PostMessageToComWnd(UINT nMsg)
{
    bool const ret = PostMessageW(GetSalData()->mpInstance->mhComWnd, nMsg, 0, 0);
    SAL_WARN_IF(!ret, "vcl.schedule", "ERROR: PostMessage() failed!");
}
}

void WinScheduler::SetForceRealTimer() { PostMessageToComWnd(SAL_MSG_FORCE_REAL_TIMER); }

void WinScheduler::PostDummyMessage() { PostMessageToComWnd(SAL_MSG_DUMMY); }

#endif // _WIN32

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
