/* comment */
#ifndef INCLUDED_VCL_INC_HEADLESS_SVPDUMMIES_HXX
#define INCLUDED_VCL_INC_HEADLESS_SVPDUMMIES_HXX

#include <vcl/sysdata.hxx>
#include <unx/gensys.h>
#include <salobj.hxx>

class SalGraphics;

class SvpSalObject final : public SalObject
{
public:
    SystemEnvData m_aSystemChildData;

    virtual ~SvpSalObject() override;

    // override all pure virtual methods
    virtual void                    ResetClipRegion() override;
    virtual void                    BeginSetClipRegion( sal_uInt32 nRects ) override;
    virtual void                    UnionClipRegion( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    EndSetClipRegion() override;

    virtual void                    SetPosSize( tools::Long nX, tools::Long nY, tools::Long nWidth, tools::Long nHeight ) override;
    virtual void                    Show( bool bVisible ) override;

    virtual const SystemEnvData*    GetSystemData() const override;
};

class SvpSalSystem : public SalGenericSystem
{
public:
    SvpSalSystem() {}
    virtual ~SvpSalSystem() override;
    // get info about the display
    virtual unsigned int GetDisplayScreenCount() override;
    virtual tools::Rectangle GetDisplayScreenPosSizePixel( unsigned int nScreen ) override;

    virtual int ShowNativeDialog( const OUString& rTitle,
                                  const OUString& rMessage,
                                  const std::vector< OUString >& rButtons ) override;
};

#endif // INCLUDED_VCL_INC_HEADLESS_SVPDUMMIES_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
