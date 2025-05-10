/* comment */
#ifndef INCLUDED_VCL_INC_WIN_SALSYS_H
#define INCLUDED_VCL_INC_WIN_SALSYS_H

#include <salsys.hxx>

#include <vector>
#include <map>

class WinSalSystem : public SalSystem
{
public:
    struct DisplayMonitor
    {
        OUString        m_aName;
        tools::Rectangle       m_aArea;

        DisplayMonitor() {}
        DisplayMonitor( const OUString& rName,
                        const tools::Rectangle& rArea )
                        : m_aName( rName ),
                          m_aArea( rArea )
        {
        }
    };
private:
    std::vector<DisplayMonitor>             m_aMonitors;
    std::map<OUString, unsigned int>   m_aDeviceNameToMonitor;
    unsigned int                            m_nPrimary;
public:
    WinSalSystem() : m_nPrimary( 0 ) {}
    virtual ~WinSalSystem() override;

    virtual unsigned int GetDisplayScreenCount() override;
    virtual unsigned int GetDisplayBuiltInScreen() override;
    virtual tools::Rectangle GetDisplayScreenPosSizePixel( unsigned int nScreen )  override;
    virtual int ShowNativeMessageBox( const OUString& rTitle,
                                      const OUString& rMessage)  override;
    bool initMonitors();
    // discards monitorinfo; used by WM_DISPLAYCHANGED handler
    void clearMonitors();
    const std::vector<DisplayMonitor>& getMonitors()
    { initMonitors(); return m_aMonitors;}

    bool handleMonitorCallback( sal_IntPtr /*HMONITOR*/,
                                sal_IntPtr /*HDC*/,
                                sal_IntPtr /*LPRECT*/ );
};

#endif // INCLUDED_VCL_INC_WIN_SALSYS_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
