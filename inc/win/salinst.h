/* comment */
#ifndef INCLUDED_VCL_INC_WIN_SALINST_H
#define INCLUDED_VCL_INC_WIN_SALINST_H

#include <sal/config.h>

#include <osl/conditn.hxx>

#include <salinst.hxx>

class SalYieldMutex;

class WinSalInstance : public SalInstance
{
public:
    /// Instance Handle
    HINSTANCE           mhInst;
    /// invisible Window so non-main threads can SendMessage() the main thread
    HWND                mhComWnd;

    osl::Condition      maWaitingYieldCond;
    unsigned            m_nNoYieldLock;

public:
    WinSalInstance();
    virtual ~WinSalInstance() override;

    virtual SalFrame*       CreateChildFrame( SystemParentData* pParent, SalFrameStyleFlags nStyle ) override;
    virtual SalFrame*       CreateFrame( SalFrame* pParent, SalFrameStyleFlags nStyle ) override;
    virtual void            DestroyFrame( SalFrame* pFrame ) override;
    virtual SalObject*      CreateObject( SalFrame* pParent, SystemWindowData* pWindowData, bool bShow ) override;
    virtual void            DestroyObject( SalObject* pObject ) override;
    virtual std::unique_ptr<SalVirtualDevice>
                            CreateVirtualDevice( SalGraphics& rGraphics,
                                                     tools::Long &nDX, tools::Long &nDY,
                                                     DeviceFormat eFormat, const SystemGraphicsData *pData = nullptr ) override;
    virtual SalInfoPrinter* CreateInfoPrinter( SalPrinterQueueInfo* pQueueInfo,
                                               ImplJobSetup* pSetupData ) override;
    virtual void            DestroyInfoPrinter( SalInfoPrinter* pPrinter ) override;
    virtual std::unique_ptr<SalPrinter> CreatePrinter( SalInfoPrinter* pInfoPrinter ) override;
    virtual void            GetPrinterQueueInfo( ImplPrnQueueList* pList ) override;
    virtual void            GetPrinterQueueState( SalPrinterQueueInfo* pInfo ) override;
    virtual OUString            GetDefaultPrinter() override;
    virtual SalTimer*           CreateSalTimer() override;
    virtual SalSystem*          CreateSalSystem() override;
    virtual std::shared_ptr<SalBitmap> CreateSalBitmap() override;
    virtual bool                IsMainThread() const override;

    virtual bool                DoYield(bool bWait, bool bHandleAllCurrentEvents) override;
    virtual bool                AnyInput( VclInputFlags nType ) override;
    virtual std::unique_ptr<SalMenu>     CreateMenu( bool bMenuBar, Menu* ) override;
    virtual std::unique_ptr<SalMenuItem> CreateMenuItem( const SalItemParams & rItemData ) override;
    virtual OpenGLContext*      CreateOpenGLContext() override;
    virtual OUString            GetConnectionIdentifier() override;
    virtual void                AddToRecentDocumentList(const OUString& rFileUrl, const OUString& rMimeType, const OUString& rDocumentService) override;

    virtual OUString            getOSVersion() override;
    virtual void BeforeAbort(const OUString&, bool) override;

    static int WorkaroundExceptionHandlingInUSER32Lib(int nExcept, LPEXCEPTION_POINTERS pExceptionInfo);

    virtual css::uno::Reference<css::uno::XInterface> ImplCreateDragSource(const SystemEnvData*) override;
    virtual css::uno::Reference<css::uno::XInterface> ImplCreateDropTarget(const SystemEnvData*) override;
};

SalFrame* ImplSalCreateFrame( WinSalInstance* pInst, HWND hWndParent, SalFrameStyleFlags nSalFrameStyle );
SalObject* ImplSalCreateObject( WinSalInstance* pInst, WinSalFrame* pParent );
HWND ImplSalReCreateHWND( HWND hWndParent, HWND oldhWnd, bool bAsChild );
bool OSSupportsDarkMode();

#endif // INCLUDED_VCL_INC_WIN_SALINST_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
