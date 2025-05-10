/* comment */
#include <sal/config.h>

#include <string_view>

#include <QtInstance.hxx>
#include <QtPrinter.hxx>

#include <vcl/svapp.hxx>
#include <vcl/timer.hxx>
#include <vcl/QueueInfo.hxx>
#include <printerinfomanager.hxx>

#include <jobset.h>
#include <print.h>
#include <salptype.hxx>

#include <unx/genpspgraphics.h>

using namespace psp;

/*
 *  static helpers
 */

static OUString getPdfDir(const PrinterInfo& rInfo)
{
    OUString aDir;
    sal_Int32 nIndex = 0;
    while (nIndex != -1)
    {
        OUString aToken(rInfo.m_aFeatures.getToken(0, ',', nIndex));
        if (aToken.startsWith("pdf="))
        {
            sal_Int32 nPos = 0;
            aDir = aToken.getToken(1, '=', nPos);
            if (aDir.isEmpty())
                if (auto const env = getenv("HOME"))
                {
                    aDir = OStringToOUString(std::string_view(env), osl_getThreadTextEncoding());
                }
            break;
        }
    }
    return aDir;
}

SalInfoPrinter* QtInstance::CreateInfoPrinter(SalPrinterQueueInfo* pQueueInfo,
                                              ImplJobSetup* pJobSetup)
{
    // create and initialize SalInfoPrinter
    PspSalInfoPrinter* pPrinter = new PspSalInfoPrinter;
    configurePspInfoPrinter(pPrinter, pQueueInfo, pJobSetup);

    return pPrinter;
}

void QtInstance::DestroyInfoPrinter(SalInfoPrinter* pPrinter) { delete pPrinter; }

std::unique_ptr<SalPrinter> QtInstance::CreatePrinter(SalInfoPrinter* pInfoPrinter)
{
    // create and initialize SalPrinter
    QtPrinter* pPrinter = new QtPrinter(pInfoPrinter);
    pPrinter->m_aJobData = static_cast<PspSalInfoPrinter*>(pInfoPrinter)->m_aJobData;

    return std::unique_ptr<SalPrinter>(pPrinter);
}

void QtInstance::GetPrinterQueueInfo(ImplPrnQueueList* pList)
{
    PrinterInfoManager& rManager(PrinterInfoManager::get());
    static const char* pNoSyncDetection = getenv("SAL_DISABLE_SYNCHRONOUS_PRINTER_DETECTION");
    if (!pNoSyncDetection || !*pNoSyncDetection)
    {
        // #i62663# synchronize possible asynchronouse printer detection now
        rManager.checkPrintersChanged(true);
    }
    ::std::vector<OUString> aPrinters;
    rManager.listPrinters(aPrinters);

    for (const auto& rPrinter : aPrinters)
    {
        const PrinterInfo& rInfo(rManager.getPrinterInfo(rPrinter));
        // create new entry
        std::unique_ptr<SalPrinterQueueInfo> pInfo(new SalPrinterQueueInfo);
        pInfo->maPrinterName = rPrinter;
        pInfo->maDriver = rInfo.m_aDriverName;
        pInfo->maLocation = rInfo.m_aLocation;
        pInfo->maComment = rInfo.m_aComment;

        sal_Int32 nIndex = 0;
        while (nIndex != -1)
        {
            OUString aToken(rInfo.m_aFeatures.getToken(0, ',', nIndex));
            if (aToken.startsWith("pdf="))
            {
                pInfo->maLocation = getPdfDir(rInfo);
                break;
            }
        }

        pList->Add(std::move(pInfo));
    }
}

void QtInstance::GetPrinterQueueState(SalPrinterQueueInfo*) {}

OUString QtInstance::GetDefaultPrinter()
{
    PrinterInfoManager& rManager(PrinterInfoManager::get());
    return rManager.getDefaultPrinter();
}

void QtInstance::PostPrintersChanged() {}

std::unique_ptr<GenPspGraphics> QtInstance::CreatePrintGraphics()
{
    return std::make_unique<GenPspGraphics>();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
