/* comment */
#ifndef INCLUDED_VCL_INC_GENERIC_GENSYS_H
#define INCLUDED_VCL_INC_GENERIC_GENSYS_H

#include <salsys.hxx>
#include <vector>

/*
 * Helps de-tangle the rather horrible ShowNativeMessageBox API
 */
class VCL_DLLPUBLIC SalGenericSystem : public SalSystem
{
 public:
    SalGenericSystem();
    virtual ~SalGenericSystem() override;
    virtual int ShowNativeDialog( const OUString& rTitle,
                                  const OUString& rMessage,
                                  const std::vector< OUString >& rButtons ) = 0;

    virtual int ShowNativeMessageBox( const OUString& rTitle,
                                      const OUString& rMessage) override;

#if !defined(ANDROID) && !defined(IOS)
    // Simple helpers for X11 WM_CLASS hints
    static const char *getFrameResName();
    static const char *getFrameClassName();
#endif
};

#endif // INCLUDED_VCL_INC_GENERIC_GENSYS_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
