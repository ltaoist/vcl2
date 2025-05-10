/* comment */
#pragma once

#include "osxvcltypes.h"
#include "a11ywrapper.h"
#include <com/sun/star/accessibility/XAccessibleContext.hpp>

@interface AquaA11yFactory : NSObject
{
}
+(void)insertIntoWrapperRepository: (NSView *) viewElement forAccessibleContext: (css::uno::Reference < css::accessibility::XAccessibleContext >) rxAccessibleContext;
+(AquaA11yWrapper *)wrapperForAccessible: (css::uno::Reference < css::accessibility::XAccessible >) rxAccessible;
+(AquaA11yWrapper *)wrapperForAccessibleContext: (css::uno::Reference < css::accessibility::XAccessibleContext >) rxAccessibleContext;
+(AquaA11yWrapper *)wrapperForAccessibleContext: (css::uno::Reference < css::accessibility::XAccessibleContext >) rxAccessibleContext createIfNotExists:(BOOL) bCreate;
+(AquaA11yWrapper *)wrapperForAccessibleContext: (css::uno::Reference < css::accessibility::XAccessibleContext >) rxAccessibleContext createIfNotExists:(BOOL) bCreate asRadioGroup:(BOOL) asRadioGroup;
+(void)removeFromWrapperRepositoryFor: (css::uno::Reference < css::accessibility::XAccessibleContext >) rxAccessibleContext;
+(void)registerView: (NSView *) theView;
+(void)revokeView: (NSView *) theViewt;
@end


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
