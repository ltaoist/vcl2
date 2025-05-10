/* comment */

#pragma once

#include <unx/gendata.hxx>

class SvpSalData : public GenericUnixSalData
{
public:
    explicit SvpSalData()
        : GenericUnixSalData()
    {
    }
    virtual void ErrorTrapPush() override {}
    virtual bool ErrorTrapPop(bool /*bIgnoreError*/ = true) override { return false; }
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
