/* comment */
#ifndef INCLUDED_VCL_INC_IOS_IOSINST_HXX
#define INCLUDED_VCL_INC_IOS_IOSINST_HXX

#include <premac.h>
#include <CoreGraphics/CoreGraphics.h>
#include <postmac.h>

#include <tools/link.hxx>

#include "headless/svpinst.hxx"
#include "headless/svpframe.hxx"

class IosSalFrame;
class IosSalInstance : public SvpSalInstance
{
public:
    IosSalInstance(std::unique_ptr<SalYieldMutex> pMutex);
    virtual ~IosSalInstance();
    static IosSalInstance* getInstance();

    SalSystem* CreateSalSystem() override;

    css::uno::Reference<css::uno::XInterface>
    CreateClipboard(const css::uno::Sequence<css::uno::Any>& i_rArguments) override;

    void GetWorkArea(tools::Rectangle& rRect);
    SalFrame* CreateFrame(SalFrame* pParent, SalFrameStyleFlags nStyle) override;
    SalFrame* CreateChildFrame(SystemParentData* pParent, SalFrameStyleFlags nStyle) override;
};

#endif // INCLUDED_VCL_INC_IOS_IOSINST_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
