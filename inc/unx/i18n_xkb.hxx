/* comment */
#ifndef INCLUDED_VCL_INC_UNX_I18N_XKB_HXX
#define INCLUDED_VCL_INC_UNX_I18N_XKB_HXX

#include <X11/Xlib.h>

#include <vclpluginapi.h>

class SalI18N_KeyboardExtension
{
private:

    bool                mbUseExtension;
    int                 mnEventBase;

public:

                        SalI18N_KeyboardExtension( Display *pDisplay );

    inline bool     UseExtension() const ;      // server and client support the
                                                    // extension
    inline void         UseExtension( bool bState );// used to disable the Extension

    void                Dispatch( XEvent *pEvent ); // keep track of group changes

    inline int          GetEventBase() const ;
};

inline bool
SalI18N_KeyboardExtension::UseExtension() const
{
    return mbUseExtension;
}

inline void
SalI18N_KeyboardExtension::UseExtension( bool bState )
{
    mbUseExtension = mbUseExtension && bState;
}

inline int
SalI18N_KeyboardExtension::GetEventBase() const
{
    return mnEventBase;
}

#endif // INCLUDED_VCL_INC_UNX_I18N_XKB_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
