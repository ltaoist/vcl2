/* comment */
#pragma once

#include <cppuhelper/compbase.hxx>

#include <com/sun/star/datatransfer/clipboard/XClipboardManager.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <map>

typedef std::map< OUString, css::uno::Reference< css::datatransfer::clipboard::XClipboard > > ClipboardMap;

namespace dtrans
{

    class ClipboardManager : public ::cppu::WeakComponentImplHelper <
      css::datatransfer::clipboard::XClipboardManager,
      css::lang::XEventListener,
      css::lang::XServiceInfo >
    {
        ClipboardMap m_aClipboardMap;
        ::osl::Mutex m_aMutex;

        const OUString m_aDefaultName;

        virtual ~ClipboardManager() override;
    protected:
        using WeakComponentImplHelperBase::disposing;
    public:

        ClipboardManager();

        /*
         * XServiceInfo
         */

        virtual OUString SAL_CALL getImplementationName(  ) override;

        virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) override;

        virtual css::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames(  ) override;

        /*
         * XComponent
         */

        virtual void SAL_CALL dispose() override;

        /*
         * XEventListener
         */

        virtual void SAL_CALL disposing( const css::lang::EventObject& Source ) override;

        /*
         * XClipboardManager
         */

        virtual css::uno::Reference< css::datatransfer::clipboard::XClipboard > SAL_CALL getClipboard( const OUString& aName ) override;

        virtual void SAL_CALL addClipboard( const css::uno::Reference< css::datatransfer::clipboard::XClipboard >& xClipboard ) override;

        virtual void SAL_CALL removeClipboard( const OUString& aName ) override;

        virtual css::uno::Sequence< OUString > SAL_CALL listClipboardNames(  ) override;

    };

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
