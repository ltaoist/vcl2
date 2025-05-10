/* comment */
#pragma once

#include "osxvcltypes.h"
#include <com/sun/star/accessibility/XAccessibleAction.hpp>
#include <com/sun/star/accessibility/XAccessibleContext.hpp>
#include <com/sun/star/accessibility/XAccessibleComponent.hpp>
#include <com/sun/star/accessibility/XAccessibleExtendedComponent.hpp>
#include <com/sun/star/accessibility/XAccessibleSelection.hpp>
#include <com/sun/star/accessibility/XAccessibleTable.hpp>
#include <com/sun/star/accessibility/XAccessibleText.hpp>
#include <com/sun/star/accessibility/XAccessibleTextAttributes.hpp>
#include <com/sun/star/accessibility/XAccessibleEditableText.hpp>
#include <com/sun/star/accessibility/XAccessibleValue.hpp>
#include <com/sun/star/accessibility/XAccessibleMultiLineText.hpp>
#include <com/sun/star/accessibility/XAccessibleTextMarkup.hpp>

// rAccessibleXYZ as a field in an Objective-C-Class would not call Con-/Destructor, so use a struct instead
struct ReferenceWrapper
{
    css::uno::Reference < css::accessibility::XAccessibleAction > rAccessibleAction;
    css::uno::Reference < css::accessibility::XAccessibleContext > rAccessibleContext;
    css::uno::Reference < css::accessibility::XAccessibleComponent > rAccessibleComponent;
    css::uno::Reference < css::accessibility::XAccessibleExtendedComponent > rAccessibleExtendedComponent;
    css::uno::Reference < css::accessibility::XAccessibleSelection > rAccessibleSelection;
    css::uno::Reference < css::accessibility::XAccessibleTable > rAccessibleTable;
    css::uno::Reference < css::accessibility::XAccessibleText > rAccessibleText;
    css::uno::Reference < css::accessibility::XAccessibleEditableText > rAccessibleEditableText;
    css::uno::Reference < css::accessibility::XAccessibleValue > rAccessibleValue;
    css::uno::Reference < css::accessibility::XAccessibleTextAttributes > rAccessibleTextAttributes;
    css::uno::Reference < css::accessibility::XAccessibleMultiLineText > rAccessibleMultiLineText;
    css::uno::Reference < css::accessibility::XAccessibleTextMarkup > rAccessibleTextMarkup;
};

@interface AquaA11yWrapper : NSView
{
    ReferenceWrapper * mpReferenceWrapper;
    BOOL mActsAsRadioGroup;
    BOOL mIsTableCell;
}
// NSAccessibility Protocol
-(id)accessibilityAttributeValue:(NSString *)attribute;
-(BOOL)accessibilityIsIgnored;
-(NSArray *)accessibilityAttributeNames;
-(BOOL)accessibilityIsAttributeSettable:(NSString *)attribute;
-(NSArray *)accessibilityParameterizedAttributeNames;
-(BOOL)accessibilitySetOverrideValue:(id)value forAttribute:(NSString *)attribute;
-(void)accessibilitySetValue:(id)value forAttribute:(NSString *)attribute;
-(id)accessibilityAttributeValue:(NSString *)attribute forParameter:(id)parameter;
-(id)accessibilityFocusedUIElement;
-(NSString *)accessibilityActionDescription:(NSString *)action;
-(void)accessibilityPerformAction:(NSString *)action;
-(NSArray *)accessibilityActionNames;
-(id)accessibilityHitTest:(NSPoint)point;
// Attribute values
-(id)parentAttribute;
-(id)valueAttribute;
-(id)titleAttribute;
-(id)helpAttribute;
-(id)numberOfCharactersAttribute;
-(id)selectedTextAttribute;
-(id)selectedTextRangeAttribute;
-(id)visibleCharacterRangeAttribute;
-(id)childrenAttribute;
-(id)orientationAttribute;
-(id)windowAttribute;
// Wrapper-specific
-(void)setActsAsRadioGroup:(BOOL)actsAsRadioGroup;
-(BOOL)actsAsRadioGroup;
-(NSWindow*)windowForParent;
-(id)initWithAccessibleContext: (css::uno::Reference < css::accessibility::XAccessibleContext >) anAccessibleContext;
-(void) setDefaults: (css::uno::Reference < css::accessibility::XAccessibleContext >) rxAccessibleContext;
-(void) dealloc;
+(void)setPopupMenuOpen:(BOOL)popupMenuOpen;
-(css::accessibility::XAccessibleAction *)accessibleAction;
-(css::accessibility::XAccessibleContext *)accessibleContext;
-(css::accessibility::XAccessibleComponent *)accessibleComponent;
-(css::accessibility::XAccessibleExtendedComponent *)accessibleExtendedComponent;
-(css::accessibility::XAccessibleSelection *)accessibleSelection;
-(css::accessibility::XAccessibleTable *)accessibleTable;
-(css::accessibility::XAccessibleText *)accessibleText;
-(css::accessibility::XAccessibleEditableText *)accessibleEditableText;
-(css::accessibility::XAccessibleValue *)accessibleValue;
-(css::accessibility::XAccessibleTextAttributes *)accessibleTextAttributes;
-(css::accessibility::XAccessibleMultiLineText *)accessibleMultiLineText;
-(css::accessibility::XAccessibleTextMarkup *)accessibleTextMarkup;
@end


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
