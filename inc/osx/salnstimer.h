/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALNSTIMER_H
#define INCLUDED_VCL_INC_OSX_SALNSTIMER_H

#include <premac.h>
#include <Cocoa/Cocoa.h>
#include <postmac.h>

@interface TimerCallbackCaller : NSObject
{
}
- (void)timerElapsed:(NSTimer*)pTimer;
@end

#endif // INCLUDED_VCL_INC_OSX_SALNSTIMER_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
