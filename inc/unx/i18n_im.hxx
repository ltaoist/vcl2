/* comment */
#ifndef INCLUDED_VCL_INC_UNX_I18N_IM_HXX
#define INCLUDED_VCL_INC_UNX_I18N_IM_HXX

#include <X11/Xlib.h>

#include <vclpluginapi.h>

#define bUseInputMethodDefault True

class SalI18N_InputMethod
{
    bool        mbUseable;  // system supports locale as well as status
                            // and preedit style ?
    XIM         maMethod;
    XIMCallback maDestroyCallback;
    XIMStyles  *mpStyles;

public:

    Bool        PosixLocale();
    bool        UseMethod() const      { return mbUseable; }
    XIM         GetMethod() const      { return maMethod;  }
    void        HandleDestroyIM();
    void        CreateMethod( Display *pDisplay );
    XIMStyles  *GetSupportedStyles()    { return mpStyles;  }
    void        SetLocale();
    bool        FilterEvent( XEvent *pEvent, ::Window window );

    SalI18N_InputMethod();
    ~SalI18N_InputMethod();
};

#endif // INCLUDED_VCL_INC_UNX_I18N_IM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
