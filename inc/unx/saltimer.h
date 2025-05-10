/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALTIMER_H
#define INCLUDED_VCL_INC_UNX_SALTIMER_H

#include <saltimer.hxx>

class SalXLib;
class X11SalTimer final : public SalTimer
{
    SalXLib *mpXLib;
public:
    X11SalTimer( SalXLib *pXLib ) : mpXLib( pXLib ) {}
    virtual ~X11SalTimer() override;

    // override all pure virtual methods
    void  Start( sal_uInt64 nMS ) override;
    void  Stop() override;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
