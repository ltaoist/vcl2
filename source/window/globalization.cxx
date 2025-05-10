/* comment */
#include <vcl/window.hxx>
#include <vcl/outdev.hxx>
#include <windowdev.hxx>
#include <window.h>

namespace vcl {

void WindowOutputDevice::EnableRTL ( bool bEnable )
{
    if (mbEnableRTL != bEnable)
        mxOwnerWindow->ImplEnableRTL(bEnable);
}

void Window::ImplEnableRTL( bool bEnable )
{
    if (mpWindowImpl->mxOutDev->mbEnableRTL != bEnable)
    {
        CompatStateChanged( StateChangedType::Mirroring );
        mpWindowImpl->mxOutDev->OutputDevice::EnableRTL(bEnable);
    }
}

} /* namespace vcl */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
