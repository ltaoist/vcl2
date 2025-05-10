/* comment */
#pragma once

#include <sal/config.h>

#include <memory>
#include <comphelper/solarmutex.hxx>
#include <salinst.hxx>
#include <svdata.hxx>
#include <unx/genprn.h>

class VCL_DLLPUBLIC SalYieldMutex : public comphelper::SolarMutex
{
public:
    SalYieldMutex();
    virtual ~SalYieldMutex() override;
};

/*
 * Abstract generic class to build vclplugin's instance classes from
 */
class GenPspGraphics;
namespace vcl::font
{
    class PhysicalFontCollection;
}

class VCL_DLLPUBLIC SalGenericInstance : public SalInstance
{
protected:
    bool           mbPrinterInit;

public:
    SalGenericInstance( std::unique_ptr<comphelper::SolarMutex> pMutex )
        : SalInstance(std::move(pMutex)), mbPrinterInit(false) {}
    virtual ~SalGenericInstance() override;

    // Printing
    virtual SalInfoPrinter*     CreateInfoPrinter      ( SalPrinterQueueInfo* pQueueInfo,
                                                         ImplJobSetup* pSetupData ) override;
    virtual void                DestroyInfoPrinter     ( SalInfoPrinter* pPrinter ) override;
    virtual std::unique_ptr<SalPrinter> CreatePrinter  ( SalInfoPrinter* pInfoPrinter ) override;
    virtual void                GetPrinterQueueInfo    ( ImplPrnQueueList* pList ) override;
    virtual void                GetPrinterQueueState   ( SalPrinterQueueInfo* pInfo ) override;
    virtual OUString            GetDefaultPrinter() override;
    virtual void                PostPrintersChanged() = 0;
    virtual void                updatePrinterUpdate() override;
    virtual void                jobStartedPrinterUpdate() override;
    virtual void                jobEndedPrinterUpdate() override;
    bool isPrinterInit() const { return mbPrinterInit; }
    virtual std::unique_ptr<GenPspGraphics> CreatePrintGraphics() = 0;

    virtual OUString            getOSVersion() override;

    // prolly belongs somewhere else ... just a font help
    static void RegisterFontSubstitutors( vcl::font::PhysicalFontCollection* pFontCollection );

protected:
    static void configurePspInfoPrinter( PspSalInfoPrinter* pInfoPrinter,
                                         SalPrinterQueueInfo const * pQueueInfo,
                                         ImplJobSetup* pSetupData );
};

inline SalGenericInstance *GetGenericInstance()
{
    return static_cast<SalGenericInstance*>(GetSalInstance());
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
