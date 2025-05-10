/* comment */
#include <vcl/wrkwin.hxx>
#include <vcl/introwin.hxx>

#include <svdata.hxx>

void IntroWindow::ImplInitIntroWindowData()
{
    ImplSVData* pSVData = ImplGetSVData();
    pSVData->mpIntroWindow = this;
}

IntroWindow::IntroWindow()
    : WorkWindow(WindowType::INTROWINDOW)
{
    ImplInitIntroWindowData();
    WorkWindow::ImplInit(nullptr, WB_INTROWIN);
}

IntroWindow::~IntroWindow() { disposeOnce(); }

void IntroWindow::dispose()
{
    ImplSVData* pSVData = ImplGetSVData();
    if (pSVData->mpIntroWindow.get() == this)
        pSVData->mpIntroWindow = nullptr;

    WorkWindow::dispose();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
