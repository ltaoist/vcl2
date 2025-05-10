/* comment */

#ifndef INCLUDED_VCL_INC_SKIA_OSX_BITMAP_HXX
#define INCLUDED_VCL_INC_SKIA_OSX_BITMAP_HXX

#include <vcl/dllapi.h>

#include <osx/osxvcltypes.h>

class Image;

namespace SkiaHelper
{
VCL_PLUGIN_PUBLIC CGImageRef createCGImage(const Image& rImage);
};

#endif // INCLUDED_VCL_INC_SKIA_OSX_BITMAP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
