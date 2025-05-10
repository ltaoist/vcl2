/* comment */
#ifndef INCLUDED_VCL_INC_QUARTZ_CTFONTS_HXX
#define INCLUDED_VCL_INC_QUARTZ_CTFONTS_HXX

#include <quartz/salgdi.h>
#include <sallayout.hxx>

std::unique_ptr<SystemFontList> GetCoretextFontList();
FontAttributes DevFontFromCTFontDescriptor(CTFontDescriptorRef, bool*);

#endif // INCLUDED_VCL_INC_QUARTZ_CTFONTS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
