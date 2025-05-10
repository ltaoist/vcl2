/* comment */

#ifndef INCLUDED_VCL_INC_SALGRADIENT_HXX
#define INCLUDED_VCL_INC_SALGRADIENT_HXX

#include <basegfx/point/b2dpoint.hxx>

struct SalGradientStop
{
    Color maColor;
    float mfOffset;

    SalGradientStop(Color const& rColor, float fOffset)
        : maColor(rColor)
        , mfOffset(fOffset)
    {
    }
};

struct SalGradient
{
    basegfx::B2DPoint maPoint1;
    basegfx::B2DPoint maPoint2;
    std::vector<SalGradientStop> maStops;
};

#endif // INCLUDED_VCL_INC_SALGRADIENT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
