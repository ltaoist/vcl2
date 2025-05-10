/* comment */

#ifndef INCLUDED_VCL_INC_UNX_X11_X11GDIIMPL_HXX
#define INCLUDED_VCL_INC_UNX_X11_X11GDIIMPL_HXX

#include <ControlCacheKey.hxx>

class ControlCacheKey;

class X11GraphicsImpl
{
public:
    virtual ~X11GraphicsImpl(){};
    virtual void Flush(){};
};

#endif // INCLUDED_VCL_INC_UNX_X11_X11GDIIMPL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
