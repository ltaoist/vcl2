/* comment */
#include "DtObjFactory.hxx"
#include "XTDataObject.hxx"

using namespace com::sun::star::uno;
using namespace com::sun::star::datatransfer;
using namespace com::sun::star::lang;

IDataObjectPtr
CDTransObjFactory::createDataObjFromTransferable(const Reference<XComponentContext>& rxContext,
                                                 const Reference<XTransferable>& refXTransferable)
{
    return (IDataObjectPtr(new CXTDataObject(rxContext, refXTransferable)));
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
