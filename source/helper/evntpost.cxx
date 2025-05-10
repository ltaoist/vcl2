/* comment */
#include <sal/config.h>

#include <tools/debug.hxx>
#include <vcl/evntpost.hxx>
#include <vcl/svapp.hxx>

namespace vcl
{

EventPoster::EventPoster( const Link<LinkParamNone*,void>& rLink )
    : m_aLink(rLink)
{
    m_nId = nullptr;
}

EventPoster::~EventPoster()
{
    DBG_TESTSOLARMUTEX();
    if ( m_nId )
        Application::RemoveUserEvent( m_nId );
}

void EventPoster::Post()
{
    DBG_TESTSOLARMUTEX();
    m_nId = Application::PostUserEvent( LINK( this, EventPoster, DoEvent_Impl ) );
}

IMPL_LINK( EventPoster, DoEvent_Impl, void*, /*p*/, void )
{
    DBG_TESTSOLARMUTEX();
    m_nId = nullptr;
    m_aLink.Call( nullptr );
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
