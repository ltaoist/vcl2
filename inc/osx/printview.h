/* comment */
#ifndef INCLUDED_VCL_INC_OSX_PRINTVIEW_H
#define INCLUDED_VCL_INC_OSX_PRINTVIEW_H

#include <premac.h>
#include <Cocoa/Cocoa.h>
#include <postmac.h>

#include <vcl/print.hxx>

class AquaSalInfoPrinter;

struct PrintAccessoryViewState
{
    bool        bNeedRestart;
    sal_Int32   nLastPage;

    PrintAccessoryViewState()
    : bNeedRestart( false ), nLastPage( 0 ) {}
};

@interface AquaPrintView : NSView
{
    vcl::PrinterController*     mpController;
    AquaSalInfoPrinter*         mpInfoPrinter;
}
-(id)initWithController: (vcl::PrinterController*)pController
        withInfoPrinter: (AquaSalInfoPrinter*)pInfoPrinter;
-(BOOL)knowsPageRange: (NSRangePointer)range;
-(NSRect)rectForPage: (int)page;
-(NSPoint)locationOfPrintRect: (NSRect)aRect;
-(void)drawRect: (NSRect)rect;
@end

@interface AquaPrintAccessoryView : NSObject
{
}
+(NSObject*)setupPrinterPanel: (NSPrintOperation*)pOp
               withController: (vcl::PrinterController*)pController
                    withState: (PrintAccessoryViewState*)pState;
@end

#endif // INCLUDED_VCL_INC_OSX_PRINTVIEW_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
