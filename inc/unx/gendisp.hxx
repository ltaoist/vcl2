/* comment */
#ifndef INCLUDED_VCL_INC_GENERIC_GENDISP_HXX
#define INCLUDED_VCL_INC_GENERIC_GENDISP_HXX

#include <salwtype.hxx>
#include <vcl/dllapi.h>
#include <salusereventlist.hxx>

class SalFrame;
class VCL_DLLPUBLIC SalGenericDisplay : public SalUserEventList
{
protected:
    SalFrame* m_pCapture;

    virtual void ProcessEvent( SalUserEvent aEvent ) override;

public:
                 SalGenericDisplay();
    virtual      ~SalGenericDisplay() override;

    void registerFrame( SalFrame* pFrame );
    virtual void deregisterFrame( SalFrame* pFrame );
    void emitDisplayChanged();

    void SendInternalEvent( SalFrame* pFrame, void* pData, SalEvent nEvent = SalEvent::UserEvent );
    void CancelInternalEvent( SalFrame* pFrame, void* pData, SalEvent nEvent );
    bool DispatchInternalEvent( bool bHandleAllCurrentEvent = false );

    bool     MouseCaptured( const SalFrame *pFrameData ) const
                        { return m_pCapture == pFrameData; }
    SalFrame*    GetCaptureFrame() const
                        { return m_pCapture; }
};

#endif // INCLUDED_VCL_INC_GENERIC_GENDISP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
