/* comment */
#ifndef INCLUDED_VCL_INC_UNX_CUPSMGR_HXX
#define INCLUDED_VCL_INC_UNX_CUPSMGR_HXX

#include <printerinfomanager.hxx>
#include <osl/thread.h>
#include <osl/mutex.hxx>

namespace psp
{

class PPDParser;

struct FPtrHash
{
    size_t operator()(const FILE* pPtr) const
    { return reinterpret_cast<size_t>(pPtr); }
};

class CUPSManager final : public PrinterInfoManager
{
    std::unordered_map< FILE*, OString, FPtrHash >         m_aSpoolFiles;
    int                                                    m_nDests;
    void*                                                  m_pDests;
    bool                                                   m_bNewDests;
    std::unordered_map< OUString, int >      m_aCUPSDestMap;

    std::unordered_map< OUString, PPDContext > m_aDefaultContexts;

    OString                                                m_aUser;
    /** this is a security risk, but the CUPS API demands
        to deliver a pointer to a static buffer containing
        the password, so this cannot be helped*/
    OString                                                m_aPassword;

    osl::Mutex                                                  m_aCUPSMutex;
    oslThread                                                   m_aDestThread;

    osl::Mutex                                                  m_aGetPPDMutex;
    bool                                                        m_bPPDThreadRunning;

    CUPSManager();
    virtual ~CUPSManager() override;

    virtual void initialize() override;

    static void getOptionsFromDocumentSetup( const JobData& rJob, bool bBanner, int& rNumOptions, void** rOptions );
    void runDests();
    OString threadedCupsGetPPD(const char* pPrinter);
public:
    static void runDestThread(void* pMgr);

    static CUPSManager* tryLoadCUPS();

    /// wraps cupsGetPPD, so unlink after use !
    const PPDParser* createCUPSParser( const OUString& rPrinter );

    const char* authenticateUser();

    virtual FILE* startSpool( const OUString& rPrinterName, bool bQuickCommand ) override;
    virtual bool endSpool( const OUString& rPrinterName, const OUString& rJobTitle, FILE* pFile, const JobData& rDocumentJobData, bool bBanner, const OUString& rFaxNumber ) override;
    virtual void setupJobContextData( JobData& rData ) override;

    /// check if the printer configuration has changed
    virtual bool checkPrintersChanged( bool bWait ) override;
};

} // namespace psp

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
