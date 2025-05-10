/* comment */
#pragma once

#include <tools/stream.hxx>
#include <tools/degree.hxx>

namespace exif {

enum Orientation {
    TOP_LEFT        = 1,
    TOP_RIGHT       = 2,
    BOTTOM_RIGHT    = 3,
    BOTTOM_LEFT     = 4,
    LEFT_TOP        = 5,
    RIGHT_TOP       = 6,
    RIGHT_BOTTOM    = 7,
    LEFT_BOTTOM     = 8
};
};

enum Tag {
    ORIENTATION         = 0x0112
};

class Exif final
{
private:
    exif::Orientation maOrientation;
    bool mbExifPresent;

    bool processJpeg(SvStream& rStream, bool bSetValue);
    bool processExif(SvStream& rStream, sal_uInt16 aLength, bool bSetValue);
    void processIFD(sal_uInt8* pExifData, sal_uInt16 aLength, sal_uInt16 aOffset, sal_uInt16 aNumberOfTags, bool bSetValue, bool bLittleEndian);

    struct ExifIFD {
        sal_uInt8 tag[2];
        sal_uInt8 type[2];
        sal_uInt8 count[4];
        sal_uInt8 offset[4];
    };

    struct TiffHeader {
        sal_uInt16 byteOrder;
        sal_uInt16 tagAlign;
        sal_uInt32 offset;
    };

    static exif::Orientation convertToOrientation(sal_Int32 value);

public:
    Exif();

    bool hasExif() const { return mbExifPresent;}

    exif::Orientation getOrientation() const { return maOrientation;}
    Degree10 getRotation() const;

    void setOrientation(exif::Orientation orientation);

    bool read(SvStream& rStream);
    void write(SvStream& rStream);

};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
