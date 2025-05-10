/* comment */

#pragma once

#include <string_view>

#include <xcb/xcb.h>

class QtX11Support final
{
    static constexpr const char* m_sWindowGroupName = "WM_CLIENT_LEADER\0";
    static xcb_atom_t m_nWindowGroupAtom;
    static bool m_bDidAtomLookups;

    static xcb_atom_t lookupAtom(xcb_connection_t*, const char* const sAtomName);
    static void fetchAtoms();

public:
    static bool fixICCCMwindowGroup(xcb_window_t nWinId);
    static void setApplicationID(xcb_window_t nWinId, std::u16string_view rWMClass);
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
