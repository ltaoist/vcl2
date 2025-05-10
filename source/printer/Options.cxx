/* comment */
#include <comphelper/processfactory.hxx>

#include <vcl/printer/Options.hxx>

#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/configuration/theDefaultProvider.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

namespace vcl::printer
{
void Options::ReadFromConfig(bool i_bFile)
{
    bool bSuccess = false;
    // save old state in case something goes wrong
    Options aOldValues(*this);

    // get the configuration service
    css::uno::Reference<css::lang::XMultiServiceFactory> xConfigProvider;
    css::uno::Reference<css::container::XNameAccess> xConfigAccess;
    try
    {
        // get service provider
        css::uno::Reference<css::uno::XComponentContext> xContext(
            comphelper::getProcessComponentContext());
        // create configuration hierarchical access name
        try
        {
            xConfigProvider = css::configuration::theDefaultProvider::get(xContext);

            css::beans::PropertyValue aVal;
            aVal.Name = "nodepath";
            if (i_bFile)
                aVal.Value <<= OUString("/org.openoffice.Office.Common/Print/Option/File");
            else
                aVal.Value <<= OUString("/org.openoffice.Office.Common/Print/Option/Printer");
            xConfigAccess.set(
                xConfigProvider->createInstanceWithArguments(
                    "com.sun.star.configuration.ConfigurationAccess", { css::uno::Any(aVal) }),
                css::uno::UNO_QUERY);
            if (xConfigAccess.is())
            {
                css::uno::Reference<css::beans::XPropertySet> xSet(xConfigAccess,
                                                                   css::uno::UNO_QUERY);
                if (xSet.is())
                {
                    sal_Int32 nValue = 0;
                    bool bValue = false;
                    if (xSet->getPropertyValue("ReduceTransparency") >>= bValue)
                        SetReduceTransparency(bValue);
                    if (xSet->getPropertyValue("ReducedTransparencyMode") >>= nValue)
                        SetReducedTransparencyMode(static_cast<TransparencyMode>(nValue));
                    if (xSet->getPropertyValue("ReduceGradients") >>= bValue)
                        SetReduceGradients(bValue);
                    if (xSet->getPropertyValue("ReducedGradientMode") >>= nValue)
                        SetReducedGradientMode(static_cast<GradientMode>(nValue));
                    if (xSet->getPropertyValue("ReducedGradientStepCount") >>= nValue)
                        SetReducedGradientStepCount(static_cast<sal_uInt16>(nValue));
                    if (xSet->getPropertyValue("ReduceBitmaps") >>= bValue)
                        SetReduceBitmaps(bValue);
                    if (xSet->getPropertyValue("ReducedBitmapMode") >>= nValue)
                        SetReducedBitmapMode(static_cast<BitmapMode>(nValue));
                    if (xSet->getPropertyValue("ReducedBitmapResolution") >>= nValue)
                        SetReducedBitmapResolution(static_cast<sal_uInt16>(nValue));
                    if (xSet->getPropertyValue("ReducedBitmapIncludesTransparency") >>= bValue)
                        SetReducedBitmapIncludesTransparency(bValue);
                    if (xSet->getPropertyValue("ConvertToGreyscales") >>= bValue)
                        SetConvertToGreyscales(bValue);
                    if (xSet->getPropertyValue("PDFAsStandardPrintJobFormat") >>= bValue)
                        SetPDFAsStandardPrintJobFormat(bValue);

                    bSuccess = true;
                }
            }
        }
        catch (const css::uno::Exception&)
        {
        }
    }
    catch (const css::lang::WrappedTargetException&)
    {
    }

    if (!bSuccess)
        *this = aOldValues;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
