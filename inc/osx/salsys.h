/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALSYS_H
#define INCLUDED_VCL_INC_OSX_SALSYS_H

#include <salsys.hxx>

#include <list>


class VCL_DLLPUBLIC AquaSalSystem : public SalSystem
{
public:
    AquaSalSystem() {}
    virtual ~AquaSalSystem() override;

    // get info about the display
    virtual unsigned int GetDisplayScreenCount() override;
    virtual tools::Rectangle GetDisplayScreenPosSizePixel( unsigned int nScreen ) override;

    virtual int ShowNativeMessageBox( const OUString& rTitle,
                                      const OUString& rMessage) override;
};

#endif // INCLUDED_VCL_INC_OSX_SALSYS_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
