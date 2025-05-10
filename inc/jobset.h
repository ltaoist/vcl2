/* comment */
#ifndef INCLUDED_VCL_INC_JOBSET_H
#define INCLUDED_VCL_INC_JOBSET_H

#include <rtl/ustring.hxx>
#include <i18nutil/paper.hxx>
#include <vcl/dllapi.h>
#include <vcl/prntypes.hxx>
#include <unordered_map>

// see com.sun.star.portal.client.JobSetupSystem.idl:
#define JOBSETUP_SYSTEM_WINDOWS     1
#define JOBSETUP_SYSTEM_UNIX        3
#define JOBSETUP_SYSTEM_MAC         4

class VCL_DLLPUBLIC ImplJobSetup
{
private:
    sal_uInt16      mnSystem;           //< System - JOBSETUP_SYSTEM_xxxx
    OUString        maPrinterName;      //< Printer-Name
    OUString        maDriver;           //< Driver-Name
    Orientation     meOrientation;      //< Orientation
    DuplexMode      meDuplexMode;       //< Duplex
    sal_uInt16      mnPaperBin;         //< paper bin / in tray
    Paper           mePaperFormat;      //< paper format
    tools::Long            mnPaperWidth;       //< paper width (100th mm)
    tools::Long            mnPaperHeight;      //< paper height (100th mm)
    sal_uInt32      mnDriverDataLen;    //< length of system specific data
    sal_uInt8*      mpDriverData;       //< system specific data (will be streamed a byte block)
    bool            mbPapersizeFromSetup;
    // setup mode
    PrinterSetupMode meSetupMode;
    // TODO: orig paper size
    std::unordered_map< OUString, OUString > maValueMap;

public:
    ImplJobSetup();
    ImplJobSetup( const ImplJobSetup& rJobSetup );
    ~ImplJobSetup();

    bool operator==( const ImplJobSetup& rImplJobSetup ) const;

    sal_uInt16       GetSystem() const { return mnSystem; }
    void             SetSystem(sal_uInt16 nSystem);

    const OUString&  GetPrinterName() const { return maPrinterName; }
    void             SetPrinterName(const OUString& rPrinterName);

    const OUString&  GetDriver() const { return maDriver; }
    void             SetDriver(const OUString& rDriver);

    Orientation      GetOrientation() const { return meOrientation; }
    void             SetOrientation(Orientation eOrientation);

    DuplexMode       GetDuplexMode() const { return meDuplexMode; }
    void             SetDuplexMode(DuplexMode eDuplexMode);

    sal_uInt16       GetPaperBin() const { return mnPaperBin; }
    void             SetPaperBin(sal_uInt16 nPaperBin);

    Paper            GetPaperFormat() const { return mePaperFormat; }
    void             SetPaperFormat(Paper ePaperFormat);

    tools::Long             GetPaperWidth() const { return mnPaperWidth; }
    void             SetPaperWidth(tools::Long nWidth);

    tools::Long             GetPaperHeight() const { return mnPaperHeight; }
    void             SetPaperHeight(tools::Long nHeight);

    sal_uInt32       GetDriverDataLen() const { return mnDriverDataLen; }
    void             SetDriverDataLen(sal_uInt32 nDriverDataLen);

    const sal_uInt8* GetDriverData() const { return mpDriverData; }
    void             SetDriverData(sal_uInt8* pDriverData);

    bool             GetPapersizeFromSetup() const { return mbPapersizeFromSetup; }
    void             SetPapersizeFromSetup(bool bPapersizeFromSetup);

    PrinterSetupMode GetPrinterSetupMode() const { return meSetupMode; }
    void             SetPrinterSetupMode(PrinterSetupMode eMode);

    const std::unordered_map< OUString, OUString >& GetValueMap() const
                    { return maValueMap; }
    void            SetValueMap(const OUString& rKey, const OUString& rValue);
};

// If paper format is PAPER_USER, in the system-independent part it will
// automatically be computed from paper width/height.
// If paper width/height is 0, in the system-independent part it will
// automatically be computed from paper format, if the latter is not PAPER_USER.

#endif // INCLUDED_VCL_INC_JOBSET_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
