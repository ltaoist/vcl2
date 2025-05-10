/* comment */
#ifndef INCLUDED_VCL_INC_QUARTZ_COMMON_H
#define INCLUDED_VCL_INC_QUARTZ_COMMON_H

#include <iostream>

#include <premac.h>
#ifdef MACOSX
#include <ApplicationServices/ApplicationServices.h>
#else
#include <CoreGraphics/CoreGraphics.h>
#include <CoreText/CoreText.h>
#endif
#include <postmac.h>

#include <sal/types.h>
#include <vcl/salgtype.hxx>

std::ostream &operator <<(std::ostream& s, CTFontRef pFont);

#endif // INCLUDED_VCL_INC_QUARTZ_COMMON_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
