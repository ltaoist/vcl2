/* comment */
#ifndef INCLUDED_VCL_INC_HEADLESS_SVPPRN_HXX
#define INCLUDED_VCL_INC_HEADLESS_SVPPRN_HXX

#include <unx/genprn.h>

class SvpSalInfoPrinter final : public PspSalInfoPrinter
{
public:
    virtual bool Setup(weld::Window* pFrame, ImplJobSetup* pSetupData) override;
};

class SvpSalPrinter final : public PspSalPrinter
{
public:
    SvpSalPrinter(SalInfoPrinter* pInfoPrinter);
};

#endif // INCLUDED_VCL_INC_HEADLESS_SVPPRN_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
