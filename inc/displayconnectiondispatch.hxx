/* comment */
#ifndef INCLUDED_VCL_INC_DISPLAYCONNECTIONDISPATCH_HXX
#define INCLUDED_VCL_INC_DISPLAYCONNECTIONDISPATCH_HXX

#include <sal/config.h>
#include <com/sun/star/awt/XDisplayConnection.hpp>
#include <cppuhelper/implbase.hxx>
#include <com/sun/star/uno/Reference.hxx>
#include <mutex>
#include <vector>

namespace vcl {

class DisplayConnectionDispatch final :
    public cppu::WeakImplHelper< css::awt::XDisplayConnection >
{
    std::mutex                      m_aMutex;
    ::std::vector< css::uno::Reference< css::awt::XEventHandler > >
                                    m_aHandlers;
    OUString                        m_ConnectionIdentifier;
public:
    DisplayConnectionDispatch();
    ~DisplayConnectionDispatch() override;

    void start();
    void terminate();

    bool dispatchEvent( void const * pData, int nBytes );

    // XDisplayConnection
    virtual void SAL_CALL addEventHandler( const css::uno::Any& window, const css::uno::Reference< css::awt::XEventHandler >& handler, sal_Int32 eventMask ) override;
    virtual void SAL_CALL removeEventHandler( const css::uno::Any& window, const css::uno::Reference< css::awt::XEventHandler >& handler ) override;
    virtual void SAL_CALL addErrorHandler( const css::uno::Reference< css::awt::XEventHandler >& handler ) override;
    virtual void SAL_CALL removeErrorHandler( const css::uno::Reference< css::awt::XEventHandler >& handler ) override;
    virtual css::uno::Any SAL_CALL getIdentifier() override;

};

}



#endif // INCLUDED_VCL_INC_DISPLAYCONNECTIONDISPATCH_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
