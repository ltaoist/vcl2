/* comment */

#include <vcl/WeldedTabbedNotebookbar.hxx>
#include <vcl/svapp.hxx>
#include <jsdialog/jsdialogbuilder.hxx>

WeldedTabbedNotebookbar::WeldedTabbedNotebookbar(
    const VclPtr<vcl::Window>& pContainerWindow, const OUString& rUIFilePath,
    const css::uno::Reference<css::frame::XFrame>& rFrame, sal_uInt64 nWindowId)
    : m_xBuilder(JSInstanceBuilder::CreateNotebookbarBuilder(
          pContainerWindow, AllSettings::GetUIRootDir(), rUIFilePath, rFrame, nWindowId))
{
    m_xContainer = m_xBuilder->weld_container("NotebookBar");
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
