/* comment */
#include <vcl/threadex.hxx>
#include <vcl/svapp.hxx>

using namespace vcl;

SolarThreadExecutor::SolarThreadExecutor()
    : m_bTimeout(false)
{
}

SolarThreadExecutor::~SolarThreadExecutor() {}

IMPL_LINK_NOARG(SolarThreadExecutor, worker, void*, void)
{
    if (!m_bTimeout)
    {
        m_aStart.set();
        doIt();
        m_aFinish.set();
    }
}

void SolarThreadExecutor::execute()
{
    if (Application::IsMainThread())
    {
        m_aStart.set();
        doIt();
        m_aFinish.set();
    }
    else
    {
        m_aStart.reset();
        m_aFinish.reset();
        ImplSVEvent* nEvent = Application::PostUserEvent(LINK(this, SolarThreadExecutor, worker));
        SolarMutexReleaser aReleaser;
        if (m_aStart.wait() == osl::Condition::result_timeout)
        {
            m_bTimeout = true;
            Application::RemoveUserEvent(nEvent);
        }
        else
        {
            m_aFinish.wait();
        }
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
