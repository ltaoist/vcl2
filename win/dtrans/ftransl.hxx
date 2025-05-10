/* comment */
#pragma once

#include <rtl/ustring.hxx>
#include <sal/types.h>
#include <cppuhelper/implbase.hxx>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/datatransfer/XDataFormatTranslator.hpp>
#include <com/sun/star/datatransfer/XMimeContentTypeFactory.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include "WinClip.hxx"

#include <vector>

class CDataFormatTranslatorUNO : public
    cppu::WeakImplHelper< css::datatransfer::XDataFormatTranslator,
                          css::lang::XServiceInfo >
{

public:
    explicit CDataFormatTranslatorUNO( const css::uno::Reference< css::uno::XComponentContext >& rxContext );

    // XDataFormatTranslator

    virtual css::uno::Any SAL_CALL getSystemDataTypeFromDataFlavor( const css::datatransfer::DataFlavor& aDataFlavor ) override;

    virtual css::datatransfer::DataFlavor SAL_CALL getDataFlavorFromSystemDataType( const css::uno::Any& aSysDataType ) override;

    // XServiceInfo

    virtual OUString SAL_CALL getImplementationName(  ) override;

    virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) override;

    virtual css::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames(  ) override;

private:
    const css::uno::Reference< css::uno::XComponentContext >  m_xContext;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
