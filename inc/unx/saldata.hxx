/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALDATA_HXX
#define INCLUDED_VCL_INC_UNX_SALDATA_HXX

#include <X11/Xlib.h>

#include <unx/saldisp.hxx>
#include <unx/gendata.hxx>
#include <vclpluginapi.h>

class SalXLib;
class SalDisplay;
class SalPrinter;

class X11SalData final : public GenericUnixSalData
{
    struct XErrorStackEntry
    {
        bool            m_bIgnore;
        bool            m_bWas;
        XErrorHandler   m_aHandler;
    };
    std::vector< XErrorStackEntry > m_aXErrorHandlerStack;
    XIOErrorHandler m_aOrigXIOErrorHandler;

    std::unique_ptr<SalXLib>  pXLib_;

public:
    X11SalData();
    virtual ~X11SalData() override;

    virtual void            Init();
    virtual void            Dispose() override;

    void                    DeleteDisplay(); // for shutdown

    SalXLib*                GetLib() const { return pXLib_.get(); }

    static void             Timeout();

    // X errors
    virtual void            ErrorTrapPush() override;
    virtual bool            ErrorTrapPop( bool bIgnoreError = true ) override;
    void                    XError( Display *pDisp, XErrorEvent *pEvent );
    bool                    HasXErrorOccurred() const
                                { return m_aXErrorHandlerStack.back().m_bWas; }
    void                    ResetXErrorOccurred()
                                { m_aXErrorHandlerStack.back().m_bWas = false; }
    void                    PushXErrorLevel( bool bIgnore );
    void                    PopXErrorLevel();
};

X11SalData* GetX11SalData();

#endif // INCLUDED_VCL_INC_UNX_SALDATA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
