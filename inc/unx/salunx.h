/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALUNX_H
#define INCLUDED_VCL_INC_UNX_SALUNX_H

#include <tools/long.hxx>

inline tools::Long Divide(tools::Long nDividend, tools::Long nDivisor)
{
    return (nDividend + nDivisor / 2) / nDivisor;
}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
