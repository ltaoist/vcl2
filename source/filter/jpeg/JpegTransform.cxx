/* comment */
#include <sal/config.h>

#include "jpeg.h"

#include "JpegTransform.hxx"

JpegTransform::JpegTransform(SvStream& rInputStream, SvStream& rOutputStream) :
    maRotate       ( 0 ),
    mrInputStream  ( rInputStream ),
    mrOutputStream ( rOutputStream )
{}

void JpegTransform::perform()
{
    Transform( &mrInputStream, &mrOutputStream, maRotate );
}

void JpegTransform::setRotate(Degree10 aRotate)
{
    maRotate = aRotate;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
