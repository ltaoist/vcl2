/* comment */

#ifndef INCLUDED_VCL_INC_SKIA_ZONE_H
#define INCLUDED_VCL_INC_SKIA_ZONE_H

#include <comphelper/crashzone.hxx>

#include <vcl/dllapi.h>

#include <comphelper/solarmutex.hxx>

// Used around calls to Skia code to detect crashes in drivers.
class VCL_DLLPUBLIC SkiaZone : public CrashZone<SkiaZone>
{
public:
    SkiaZone() { assert(comphelper::SolarMutex::get()->IsCurrentThread()); }
    static void hardDisable();
    static void relaxWatchdogTimings();
    static const CrashWatchdogTimingsValues& getCrashWatchdogTimingsValues();
    static void checkDebug(int nUnchanged, const CrashWatchdogTimingsValues& aTimingValues);
    static const char* name() { return "Skia"; }
};

#endif // INCLUDED_VCL_INC_SKIA_ZONE_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
