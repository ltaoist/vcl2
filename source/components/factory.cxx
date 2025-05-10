/* comment */
#include <cppuhelper/factory.hxx>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <vcl/dllapi.h>

#include <factory.hxx>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;

extern "C" {

    VCL_DLLPUBLIC void* vcl_component_getFactory(
        const char* pImplementationName,
        void* pXUnoSMgr,
        void* /*pXUnoKey*/
        )
    {
        void* pRet = nullptr;

        if( pXUnoSMgr )
        {
            Reference< css::lang::XMultiServiceFactory > xMgr(
                static_cast< css::lang::XMultiServiceFactory* >( pXUnoSMgr )
                );
            Reference< css::lang::XSingleServiceFactory > xFactory;
            if( vcl::DragSource_getImplementationName().equalsAscii( pImplementationName ) )
            {
                xFactory = ::cppu::createSingleFactory(
                    xMgr, vcl::DragSource_getImplementationName(), vcl::DragSource_createInstance,
                    vcl::DragSource_getSupportedServiceNames() );
            }
            else if( vcl::DropTarget_getImplementationName().equalsAscii( pImplementationName ) )
            {
                xFactory = ::cppu::createSingleFactory(
                    xMgr, vcl::DropTarget_getImplementationName(), vcl::DropTarget_createInstance,
                    vcl::DropTarget_getSupportedServiceNames() );
            }
            if( xFactory.is() )
            {
                xFactory->acquire();
                pRet = xFactory.get();
            }
        }
        return pRet;
    }

} /* extern "C" */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
