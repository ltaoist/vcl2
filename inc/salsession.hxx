/* comment */
#ifndef INCLUDED_VCL_INC_SALSESSION_HXX
#define INCLUDED_VCL_INC_SALSESSION_HXX

#include <vcl/dllapi.h>

enum SalSessionEventType
{
    Interaction,
    SaveRequest,
    ShutdownCancel,
    Quit
};

struct SalSessionEvent
{
    SalSessionEventType         m_eType;

    SalSessionEvent( SalSessionEventType eType )
            : m_eType( eType )
    {}
};

struct SalSessionInteractionEvent : public SalSessionEvent
{
    bool                        m_bInteractionGranted;

    SalSessionInteractionEvent( bool bGranted )
            : SalSessionEvent( Interaction ),
              m_bInteractionGranted( bGranted )
    {}
};

struct SalSessionSaveRequestEvent : public SalSessionEvent
{
    bool                        m_bShutdown;

    SalSessionSaveRequestEvent( bool bShutdown )
            : SalSessionEvent( SaveRequest ),
              m_bShutdown( bShutdown )
    {}
};

struct SalSessionShutdownCancelEvent : public SalSessionEvent
{
    SalSessionShutdownCancelEvent()
            : SalSessionEvent( ShutdownCancel )
    {}
};

struct SalSessionQuitEvent : public SalSessionEvent
{
    SalSessionQuitEvent()
            : SalSessionEvent( Quit )
    {}
};

typedef void(*SessionProc)(void *pData, SalSessionEvent *pEvent);

class VCL_PLUGIN_PUBLIC SalSession
{
    SessionProc         m_aProc;
    void *              m_pProcData;
public:
    SalSession()
        : m_aProc(nullptr)
        , m_pProcData(nullptr)
    {
    }
    virtual ~SalSession();

    void SetCallback( SessionProc aCallback, void * pCallbackData )
    {
        m_aProc = aCallback;
        m_pProcData = pCallbackData;
    }
    void CallCallback( SalSessionEvent* pEvent )
    {
        if( m_aProc )
            m_aProc( m_pProcData, pEvent );
    }

    // query the session manager for a user interaction slot
    virtual void queryInteraction() = 0;
    // signal the session manager that we're done with user interaction
    virtual void interactionDone() = 0;
    // signal that we're done saving
    virtual void saveDone() = 0;
    // try to cancel the shutdown in progress
    virtual bool cancelShutdown() = 0;
};

#endif // INCLUDED_VCL_INC_SALSESSION_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
