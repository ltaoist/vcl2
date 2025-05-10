/* comment */
#include <sal/config.h>

#include <comphelper/propertyvalue.hxx>
#include <vcl/wmfexternal.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>

// formally known as WMF_EXTERNALHEADER
WmfExternal::WmfExternal()
    : xExt(0)
    , yExt(0)
    , mapMode(0)
{
}

bool WmfExternal::setSequence(const css::uno::Sequence<css::beans::PropertyValue>& rSequence)
{
    bool bRetval(false);

    for (const auto& rPropVal : rSequence)
    {
        const OUString aName(rPropVal.Name);

        if (aName == "Width")
        {
            rPropVal.Value >>= xExt;
            bRetval = true;
        }
        else if (aName == "Height")
        {
            rPropVal.Value >>= yExt;
            bRetval = true;
        }
        else if (aName == "MapMode")
        {
            rPropVal.Value >>= mapMode;
            bRetval = true;
        }
    }

    return bRetval;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
