/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALNSMENU_H
#define INCLUDED_VCL_INC_OSX_SALNSMENU_H

class AquaSalMenu;
class AquaSalMenuItem;

@interface OOStatusItemView : NSView
{
}
- (void)drawRect:(NSRect)aRect;
- (void)layout;
- (void)mouseUp:(NSEvent*)pEvent;
@end

@interface SalNSMenu : NSMenu
{
    AquaSalMenu* mpMenu;
}
- (id)initWithMenu:(AquaSalMenu*)pMenu;
- (void)menuNeedsUpdate:(NSMenu*)pMenu;
- (void)setSalMenu:(AquaSalMenu*)pMenu;
@end

@interface SalNSMenuItem : NSMenuItem
{
    AquaSalMenuItem* mpMenuItem;
}
- (id)initWithMenuItem:(AquaSalMenuItem*)pMenuItem;
- (void)menuItemTriggered:(id)aSender;
@end

#endif // INCLUDED_VCL_INC_OSX_SALNSMENU_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
