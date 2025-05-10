/* comment */
#include <vcl/vclevent.hxx>
#include <vcl/window.hxx>
#include <vcl/menu.hxx>

#include <vcleventlisteners.hxx>

void VclEventListeners::Call( VclSimpleEvent& rEvent ) const
{
    if ( m_aListeners.empty() )
        return;

    // Copy the list, because this can be destroyed when calling a Link...
    std::vector<Link<VclSimpleEvent&,void>> aCopy( m_aListeners );
    std::vector<Link<VclSimpleEvent&,void>>::iterator aIter( aCopy.begin() );
    std::vector<Link<VclSimpleEvent&,void>>::const_iterator aEnd( aCopy.end() );
    m_updated = false;
    if (VclWindowEvent* pWindowEvent = dynamic_cast<VclWindowEvent*>(&rEvent))
    {
        VclPtr<vcl::Window> xWin(pWindowEvent->GetWindow());
        // checking mpWindowImpl to see if disposal is complete yet
        while ( aIter != aEnd && (!xWin || xWin->mpWindowImpl) )
        {
            Link<VclSimpleEvent&,void> &rLink = *aIter;
            // check this hasn't been removed in some re-enterancy scenario fdo#47368
            // But only check if the list actually has been changed.
            if( !m_updated || std::find(m_aListeners.begin(), m_aListeners.end(), rLink) != m_aListeners.end() )
                rLink.Call( rEvent );
            ++aIter;
        }
    }
    else
    {
        while ( aIter != aEnd )
        {
            Link<VclSimpleEvent&,void> &rLink = *aIter;
            if( !m_updated || std::find(m_aListeners.begin(), m_aListeners.end(), rLink) != m_aListeners.end() )
                rLink.Call( rEvent );
            ++aIter;
        }
    }
}

void VclEventListeners::addListener( const Link<VclSimpleEvent&,void>& rListener )
{
    m_aListeners.push_back( rListener );
    m_updated = true;
}

void VclEventListeners::removeListener( const Link<VclSimpleEvent&,void>& rListener )
{
    m_aListeners.erase( std::remove(m_aListeners.begin(), m_aListeners.end(), rListener ), m_aListeners.end() );
    m_updated = true;
}

VclWindowEvent::VclWindowEvent( vcl::Window* pWin, VclEventId n, void* pDat ) : VclSimpleEvent(n)
{
    pWindow = pWin; pData = pDat;
}

VclWindowEvent::~VclWindowEvent() {}

VclMenuEvent::VclMenuEvent( Menu* pM, VclEventId n, sal_uInt16 nPos )
    : VclSimpleEvent(n), pMenu(pM), mnPos(nPos)
{}

VclMenuEvent::~VclMenuEvent()
{}

Menu* VclMenuEvent::GetMenu() const
{
    return pMenu;
}


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
