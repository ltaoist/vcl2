/* comment */
#ifndef INCLUDED_VCL_INC_FACTORY_HXX
#define INCLUDED_VCL_INC_FACTORY_HXX

#include <sal/config.h>

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/uno/Sequence.hxx>
#include <rtl/ustring.hxx>

namespace com::sun::star {
    namespace lang {
        class XMultiServiceFactory;
        class XSingleServiceFactory;
    }
    namespace uno { class XInterface; }
}

namespace vcl {

css::uno::Sequence<OUString> DragSource_getSupportedServiceNames();

OUString DragSource_getImplementationName();

css::uno::Reference<css::uno::XInterface> DragSource_createInstance(
    css::uno::Reference<css::lang::XMultiServiceFactory > const &);

css::uno::Sequence<OUString> DropTarget_getSupportedServiceNames();

OUString DropTarget_getImplementationName();

css::uno::Reference<css::uno::XInterface> DropTarget_createInstance(
    css::uno::Reference<css::lang::XMultiServiceFactory > const &);

}


#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
