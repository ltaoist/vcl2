/* comment */
#include <sal/main.h>
#include <sal/log.hxx>
#include <comphelper/diagnose_ex.hxx>
#include <tools/extendapplicationenvironment.hxx>
#include <cppuhelper/bootstrap.hxx>
#include <comphelper/processfactory.hxx>
#include <i18nlangtag/languagetag.hxx>
#include <i18nlangtag/mslangid.hxx>
#include <framework/desktop.hxx>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>

#include <vcl/event.hxx>
#include <vcl/svapp.hxx>
#include <vcl/wrkwin.hxx>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace cppu;

// Forward declaration
static void Main();

SAL_IMPLEMENT_MAIN()
{
    try
    {
        tools::extendApplicationEnvironment();

        Reference< XComponentContext > xContext = defaultBootstrap_InitialComponentContext();
        Reference< XMultiServiceFactory > xServiceManager( xContext->getServiceManager(), UNO_QUERY );

        if( !xServiceManager.is() )
            Application::Abort( "Failed to bootstrap" );

        comphelper::setProcessServiceFactory( xServiceManager );

        LanguageTag::setConfiguredSystemLanguage(MsLangId::getSystemLanguage());

        InitVCL();
        ::Main();

        framework::getDesktop(::comphelper::getProcessComponentContext())->terminate();

        DeInitVCL();
    }
    catch (const Exception&)
    {
        TOOLS_WARN_EXCEPTION("vcl.app", "Fatal");
        return 1;
    }
    catch (const std::exception &e)
    {
        fprintf(stderr, "fatal error: %s\n", e.what());
        return 1;
    }

    return 0;
}

namespace {

class MyWin : public WorkWindow
{
public:
                MyWin( vcl::Window* pParent, WinBits nWinStyle );
};

}

void Main()
{
    ScopedVclPtrInstance< MyWin > aMainWin( nullptr, WB_APP | WB_STDWORK );
    aMainWin->SetText("VCL - Workbench");
    aMainWin->Show();

    Application::Execute();
}

MyWin::MyWin( vcl::Window* pParent, WinBits nWinStyle ) :
    WorkWindow( pParent, nWinStyle )
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
