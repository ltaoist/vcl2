/* comment */

#pragma once

inline tools::Long ImplMulDiv(tools::Long nNumber, tools::Long nNumerator, tools::Long nDenominator)
{
    if (!nDenominator)
        return 0;
    double n = (static_cast<double>(nNumber) * static_cast<double>(nNumerator))
               / static_cast<double>(nDenominator);
    return static_cast<tools::Long>(n);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
