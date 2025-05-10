/* comment */
#ifndef INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEGTRANSFORM_HXX
#define INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEGTRANSFORM_HXX

#include <tools/stream.hxx>

class JpegTransform final
{
    Degree10 maRotate;
    SvStream& mrInputStream;
    SvStream& mrOutputStream;

public:
    JpegTransform(SvStream& rInputStream, SvStream& rOutputStream);

    void setRotate(Degree10 aRotate);
    void perform();
};

#endif // INCLUDED_VCL_SOURCE_FILTER_JPEG_JPEGTRANSFORM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
