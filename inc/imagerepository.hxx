/* comment */
#ifndef INCLUDED_VCL_IMAGEREPOSITORY_HXX
#define INCLUDED_VCL_IMAGEREPOSITORY_HXX

#include <vcl/dllapi.h>
#include <rtl/ustring.hxx>

class BitmapEx;


namespace vcl
{


    //= ImageRepository

    // provides access to the application's image repository (image.zip)
    class ImageRepository
    {
    public:
        /** loads an image from the application's image repository
            @param  _rName
                the name of the image to load.
            @param  _out_rImage
                will take the image upon successful return.
            @return
                whether or not the image could be loaded successfully.
        */
        static bool loadImage(
            const OUString& _rName,
            BitmapEx& _out_rImage
        );
    };


} // namespace vcl


#endif // INCLUDED_VCL_IMAGEREPOSITORY_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
