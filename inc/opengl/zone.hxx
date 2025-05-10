/* comment */

#ifndef INCLUDED_VCL_INC_OPENGL_ZONE_H
#define INCLUDED_VCL_INC_OPENGL_ZONE_H

#include <sal/config.h>
#include <sal/types.h>
#include <vcl/dllapi.h>
#include <comphelper/crashzone.hxx>

/**
 * We want to be able to detect if a given crash came
 * from the OpenGL code, so use this helper to track that.
 */
class VCL_DLLPUBLIC OpenGLZone : public CrashZone<OpenGLZone>
{
public:
    static void hardDisable();
    static void relaxWatchdogTimings();
    static const CrashWatchdogTimingsValues& getCrashWatchdogTimingsValues();
    static void checkDebug(int nUnchanged, const CrashWatchdogTimingsValues& aTimingValues);
    static const char* name() { return "OpenGL"; }
};

#endif // INCLUDED_VCL_INC_OPENGL_ZONE_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
