/* comment */

#include <memory>
#include <vcl/toolkit/floatwin.hxx>
#include <vcl/uitest/uitest.hxx>
#include <vcl/uitest/uiobject.hxx>

#include <vcl/toolkit/dialog.hxx>

#include <svdata.hxx>

#include <comphelper/dispatchcommand.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>

bool UITest::executeCommand(const OUString& rCommand)
{
    return comphelper::dispatchCommand(
        rCommand,
        {{"SynchronMode", -1, css::uno::Any(true),
          css::beans::PropertyState_DIRECT_VALUE}});
}

bool UITest::executeCommandWithParameters(const OUString& rCommand,
    const css::uno::Sequence< css::beans::PropertyValue >& rArgs)
{
    css::uno::Sequence< css::beans::PropertyValue > lNewArgs =
        {{"SynchronMode", -1, css::uno::Any(true),
          css::beans::PropertyState_DIRECT_VALUE}};

    if ( rArgs.hasElements() )
    {
        sal_uInt32 nIndex( lNewArgs.getLength() );
        lNewArgs.realloc( lNewArgs.getLength()+rArgs.getLength() );

        std::copy(rArgs.begin(), rArgs.end(), std::next(lNewArgs.getArray(), nIndex));
    }
    return comphelper::dispatchCommand(rCommand,lNewArgs);
}

bool UITest::executeDialog(const OUString& rCommand)
{
    return comphelper::dispatchCommand(
        rCommand,
        {{"SynchronMode", -1, css::uno::Any(false),
          css::beans::PropertyState_DIRECT_VALUE}});
}

std::unique_ptr<UIObject> UITest::getFocusTopWindow()
{
    ImplSVData* pSVData = ImplGetSVData();
    ImplSVWinData& rWinData = *pSVData->mpWinData;

    if (!rWinData.mpExecuteDialogs.empty())
    {
        return rWinData.mpExecuteDialogs.back()->GetUITestFactory()(rWinData.mpExecuteDialogs.back());
    }

    return pSVData->maFrameData.mpFirstFrame->GetUITestFactory()(pSVData->maFrameData.mpFirstFrame);
}

std::unique_ptr<UIObject> UITest::getFloatWindow()
{
    ImplSVData* pSVData = ImplGetSVData();
    ImplSVWinData& rWinData = *pSVData->mpWinData;

    VclPtr<vcl::Window> pFloatWin = rWinData.mpFirstFloat;
    if (pFloatWin)
        return pFloatWin->GetUITestFactory()(pFloatWin);

    return nullptr;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
