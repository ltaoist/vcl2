/* comment */
#ifndef INCLUDED_VCL_INC_UNX_X11_X11SYS_HXX
#define INCLUDED_VCL_INC_UNX_X11_X11SYS_HXX

#include <unx/gensys.h>
#include <vclpluginapi.h>

class X11SalSystem final : public SalGenericSystem
{
public:
    X11SalSystem() {}
    virtual ~X11SalSystem() override;

    // override pure virtual methods
    virtual unsigned int GetDisplayScreenCount() override;
    virtual bool         IsUnifiedDisplay() override;
    virtual unsigned int GetDisplayBuiltInScreen() override;
    virtual tools::Rectangle    GetDisplayScreenPosSizePixel( unsigned int nScreen ) override;
    virtual int ShowNativeDialog( const OUString& rTitle,
                                  const OUString& rMessage,
                                  const std::vector< OUString >& rButtons ) override;
};

#endif // INCLUDED_VCL_INC_UNX_X11_X11SYS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
