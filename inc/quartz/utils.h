/* comment */
#ifndef INCLUDED_VCL_INC_QUARTZ_UTILS_H
#define INCLUDED_VCL_INC_QUARTZ_UTILS_H

#include <iostream>

#include <premac.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/Foundation.h>
#ifdef MACOSX
#include <ApplicationServices/ApplicationServices.h>
#else
#include <CoreGraphics/CoreGraphics.h>
#endif
#include <postmac.h>

#include <rtl/ustring.hxx>

OUString GetOUString( CFStringRef );
OUString GetOUString( const NSString* );
CFStringRef CreateCFString( const OUString& );
NSString* CreateNSString( const OUString& );
OUString NSStringArrayToOUString(NSArray* array);
OUString NSDictionaryKeysToOUString(NSDictionary* dict);

std::ostream &operator <<(std::ostream& s, const CGRect &rRect);
std::ostream &operator <<(std::ostream& s, const CGPoint &rPoint);
std::ostream &operator <<(std::ostream& s, const CGSize &rSize);
std::ostream &operator <<(std::ostream& s, CGColorRef pSize);
std::ostream &operator <<(std::ostream& s, const CGAffineTransform &aXform);
std::ostream &operator <<(std::ostream& s, CGColorSpaceRef cs);

#endif // INCLUDED_VCL_INC_QUARTZ_UTILS_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
