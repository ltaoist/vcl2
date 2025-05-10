/* comment */
#ifndef INCLUDED_VCL_INC_GENERIC_GENPRN_H
#define INCLUDED_VCL_INC_GENERIC_GENPRN_H

#include <jobdata.hxx>
#include <unx/printergfx.hxx>
#include <unx/printerjob.hxx>
#include <salprn.hxx>

class GenPspGraphics;
class VCL_DLLPUBLIC PspSalInfoPrinter : public SalInfoPrinter
{
public:
    std::unique_ptr<GenPspGraphics> m_pGraphics;
    psp::JobData            m_aJobData;
    psp::PrinterGfx         m_aPrinterGfx;

    PspSalInfoPrinter();
    virtual ~PspSalInfoPrinter() override;

    // override all pure virtual methods
    virtual SalGraphics*            AcquireGraphics() override;
    virtual void                    ReleaseGraphics( SalGraphics* pGraphics ) override;
    virtual bool                    Setup( weld::Window* pFrame, ImplJobSetup* pSetupData ) override;
    virtual bool                    SetPrinterData( ImplJobSetup* pSetupData ) override;
    virtual bool                    SetData( JobSetFlags nFlags, ImplJobSetup* pSetupData ) override;
    virtual void                    GetPageInfo( const ImplJobSetup* pSetupData,
                                                 tools::Long& rOutWidth, tools::Long& rOutHeight,
                                                 Point& rPageOffset,
                                                 Size& rPaperSize ) override;
    virtual sal_uInt32              GetCapabilities( const ImplJobSetup* pSetupData, PrinterCapType nType ) override;
    virtual sal_uInt16              GetPaperBinCount( const ImplJobSetup* pSetupData ) override;
    virtual OUString                GetPaperBinName( const ImplJobSetup* pSetupData, sal_uInt16 nPaperBin ) override;
    virtual void                    InitPaperFormats( const ImplJobSetup* pSetupData ) override;
    virtual int                     GetLandscapeAngle( const ImplJobSetup* pSetupData ) override;
};

class VCL_DLLPUBLIC PspSalPrinter : public SalPrinter
{
public:
    OUString                  m_aFileName;
    OUString                  m_aTmpFile;
    SalInfoPrinter*         m_pInfoPrinter;
    std::unique_ptr<GenPspGraphics> m_xGraphics;
    psp::PrinterJob         m_aPrintJob;
    psp::JobData            m_aJobData;
    psp::PrinterGfx         m_aPrinterGfx;
    sal_uInt32              m_nCopies;
    bool                    m_bCollate;
    bool                    m_bPdf;
    bool                    m_bIsPDFWriterJob;

    PspSalPrinter( SalInfoPrinter *pPrinter );
    virtual ~PspSalPrinter() override;

    // override all pure virtual methods
    virtual bool                    StartJob( const OUString* pFileName,
                                              const OUString& rJobName,
                                              const OUString& rAppName,
                                              sal_uInt32 nCopies,
                                              bool bCollate,
                                              bool bDirect,
                                              ImplJobSetup* pSetupData ) override;
    virtual bool                    StartJob( const OUString*,
                                              const OUString&,
                                              const OUString&,
                                              ImplJobSetup*,
                                              vcl::PrinterController& i_rController ) override;
    virtual bool                    EndJob() override;
    virtual SalGraphics*            StartPage( ImplJobSetup* pSetupData, bool bNewJobData ) override;
    virtual void                    EndPage() override;
};

#endif // INCLUDED_VCL_INC_GENERIC_GENPRN_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
