/* comment */

#pragma once

#include <unx/gensys.h>

class QtSystem final : public SalGenericSystem
{
public:
    virtual unsigned int GetDisplayScreenCount() override;
    virtual tools::Rectangle GetDisplayScreenPosSizePixel(unsigned int nScreen) override;
    virtual int ShowNativeDialog(const OUString& rTitle, const OUString& rMessage,
                                 const std::vector<OUString>& rButtons) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
