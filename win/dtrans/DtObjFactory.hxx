/* comment */
#pragma once

#include <com/sun/star/datatransfer/XTransferable.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>

#include <systools/win32/comtools.hxx>

namespace CDTransObjFactory
{
    IDataObjectPtr createDataObjFromTransferable( const css::uno::Reference< css::uno::XComponentContext >& rxContext,
                                                                   const css::uno::Reference< css::datatransfer::XTransferable >& refXTransferable );
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
