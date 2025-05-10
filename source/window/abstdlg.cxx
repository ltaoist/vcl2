/* comment */
#include <osl/module.hxx>
#include <vcl/abstdlg.hxx>
#include <vcl/bitmapex.hxx>

typedef VclAbstractDialogFactory*(SAL_CALL* FuncPtrCreateDialogFactory)();

#ifndef DISABLE_DYNLOADING
extern "C" {
static void thisModule() {}
}
#else
extern "C" VclAbstractDialogFactory* CreateDialogFactory();
#endif

VclAbstractDialogFactory* VclAbstractDialogFactory::Create()
{
    static auto fp = []() -> FuncPtrCreateDialogFactory {
#ifndef DISABLE_DYNLOADING
        ::osl::Module aDialogLibrary;
        if (aDialogLibrary.loadRelative(&thisModule, CUI_DLL_NAME,
                                        SAL_LOADMODULE_GLOBAL | SAL_LOADMODULE_LAZY))
        {
            auto const p = reinterpret_cast<FuncPtrCreateDialogFactory>(
                aDialogLibrary.getFunctionSymbol("CreateDialogFactory"));
            aDialogLibrary.release();
            return p;
        }
        return nullptr;
#else
        return CreateDialogFactory;
#endif
    }();
    if (fp)
        return fp();
    return nullptr;
}

VclAbstractDialog::~VclAbstractDialog() {}

bool VclAbstractDialog::StartExecuteAsync(AsyncContext&)
{
    assert(false);
    return false;
}

std::vector<OString> VclAbstractDialog::getAllPageUIXMLDescriptions() const
{
    // default has no pages
    return std::vector<OString>();
}

bool VclAbstractDialog::selectPageByUIXMLDescription(const OString& /*rUIXMLDescription*/)
{
    // default cannot select a page (which is okay, return true)
    return true;
}

BitmapEx VclAbstractDialog::createScreenshot() const
{
    // default returns empty bitmap
    return BitmapEx();
}

VclAbstractDialogFactory::~VclAbstractDialogFactory() {}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
