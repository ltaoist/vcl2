/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALDATA_HXX
#define INCLUDED_VCL_INC_OSX_SALDATA_HXX

#include <config_features.h>

#include <premac.h>
#include <Cocoa/Cocoa.h>
#include <postmac.h>

#include <com/sun/star/uno/Reference.hxx>

#include <vcl/ptrstyle.hxx>

#include <svdata.hxx>
#include <salwtype.hxx>

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>
#include <o3tl/enumarray.hxx>

#include <cstdio>
#include <cstdarg>

#include <apple_remote/RemoteMainController.h>

class AquaSalFrame;
class AquaSalInstance;
class SalObject;
class SalFrame;
class SalVirtualDevice;
class SalPrinter;
class SystemFontList;

#define SAL_CLIPRECT_COUNT 16
#define INVALID_CURSOR_PTR reinterpret_cast<NSCursor*>(0xdeadbeef)

// Singleton, instantiated from Application::Application() in
// vcl/source/app/svapp.cxx.

class SalData
{
public:
    SALTIMERPROC                                  mpTimerProc;      // timer callback proc
    AquaSalInstance                              *mpInstance;
    std::list<AquaSalFrame*>                      maPresentationFrames;  // list of frames in presentation mode
    SalObject                                    *mpFirstObject;    // pointer of first object window
    SalVirtualDevice                             *mpFirstVD;        // first VirDev
    SalPrinter                                   *mpFirstPrinter;   // first printing printer
    std::unique_ptr<SystemFontList>               mpFontList;
    NSStatusItem*                                 mpStatusItem;     // one status item that draws all our statuses
                                                                    // at the moment this is only one add menu button
    CGColorSpaceRef                               mxRGBSpace;
    CGColorSpaceRef                               mxGraySpace;

    o3tl::enumarray< PointerStyle, NSCursor* >    maCursors;
    std::vector< NSMenuItem* >                    maFallbackMenu;
    std::map< NSEvent*, bool >                    maKeyEventAnswer;

    static oslThreadKey                           s_aAutoReleaseKey;

    bool                                          mbIsScrollbarDoubleMax;   // TODO: support DoubleMin and DoubleBoth too
#if !HAVE_FEATURE_MACOSX_SANDBOX
    AppleRemoteMainController*                    mpAppleRemoteMainController;
#endif
    NSObject*                                     mpDockIconClickHandler;
    sal_Int32                                     mnDPIX;           // #i100617# read DPI only once per office life
    sal_Int32                                     mnDPIY;           // #i100617# read DPI only once per office life

    css::uno::Reference< css::uno::XInterface >   mxClipboard;

    SalData();
    ~SalData();

    NSCursor* getCursor( PointerStyle i_eStyle );

    static void ensureThreadAutoreleasePool();

    static NSStatusItem* getStatusItem();
};

bool ImplSalYieldMutexTryToAcquire();
void ImplSalYieldMutexRelease();

#endif // INCLUDED_VCL_INC_OSX_SALDATA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
