/* comment */
#ifndef INCLUDED_VCL_INC_UNX_DESKTOPS_HXX
#define INCLUDED_VCL_INC_UNX_DESKTOPS_HXX

#include <sal/config.h>

#include <sal/types.h>

enum SAL_DLLPUBLIC_RTTI DesktopType
{
    DESKTOP_NONE, // headless, i.e. no X connection at all
    DESKTOP_UNKNOWN, // unknown desktop, simple WM, etc.
    DESKTOP_GNOME,
    DESKTOP_UNITY,
    DESKTOP_XFCE,
    DESKTOP_MATE,
    DESKTOP_PLASMA5,
    DESKTOP_LXQT
}; // keep in sync with desktop_strings[] in salplug.cxx

#endif // INCLUDED_VCL_INC_UNX_DESKTOPS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
