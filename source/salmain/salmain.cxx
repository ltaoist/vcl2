/* comment */
#include <sal/config.h>
#include <config_features.h>

#include <sal/main.h>
#include <tools/extendapplicationenvironment.hxx>
#include <vcl/vclmain.hxx>
#include <vcl/svmain.hxx>

SAL_IMPLEMENT_MAIN()
{
    tools::extendApplicationEnvironment();
    vclmain::createApplication();
    return SVMain();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
