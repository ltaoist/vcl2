/* comment */
#ifndef INCLUDED_VCL_INC_SVSYS_H
#define INCLUDED_VCL_INC_SVSYS_H

#include <config_features.h>

#ifdef _WIN32
#include "win/svsys.h"
#elif defined MACOSX
#include "osx/svsys.h"
#elif defined IOS
#elif defined ANDROID
#elif defined HAIKU
#elif !HAVE_FEATURE_UI
#else
#include "unx/svsys.h"
#endif

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
