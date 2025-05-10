/* comment */
#ifndef INCLUDED_VCL_INC_UNX_GTK_GTKSYS_HXX
#define INCLUDED_VCL_INC_UNX_GTK_GTKSYS_HXX

#include <unx/gensys.h>
#include <gtk/gtk.h>
#include <unx/saltype.h>
#include <deque>

class GtkSalSystem final : public SalGenericSystem
{
    GdkDisplay *mpDisplay;
#if !GTK_CHECK_VERSION(4,0,0)
    // Number of monitors for every active screen.
    std::deque<std::pair<GdkScreen*, int> > maScreenMonitors;
#endif
public:
             GtkSalSystem();
    virtual ~GtkSalSystem() override;
    static   GtkSalSystem *GetSingleton();

    virtual bool          IsUnifiedDisplay() override;
    virtual unsigned int  GetDisplayScreenCount() override;
    virtual unsigned int  GetDisplayBuiltInScreen() override;
    virtual tools::Rectangle     GetDisplayScreenPosSizePixel   (unsigned int nScreen) override;
    virtual int           ShowNativeDialog (const OUString&              rTitle,
                                            const OUString&              rMessage,
                                            const std::vector< OUString >& rButtons) override;
    SalX11Screen      GetDisplayDefaultXScreen()
            { return getXScreenFromDisplayScreen( GetDisplayBuiltInScreen() ); }
    SalX11Screen      getXScreenFromDisplayScreen(unsigned int nDisplayScreen);
#if !GTK_CHECK_VERSION(4,0,0)
    void              countScreenMonitors();
    // We have a 'screen' number that is combined from screen-idx + monitor-idx
    int        getScreenIdxFromPtr     (GdkScreen *pScreen);
    int        getScreenMonitorIdx     (GdkScreen *pScreen, int nX, int nY);
    GdkScreen *getScreenMonitorFromIdx (int nIdx, gint &nMonitor);
#endif
};

#endif // INCLUDED_VCL_INC_UNX_GTK_GTKSYS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
