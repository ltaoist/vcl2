/* comment */
#pragma once

#include <sal/config.h>

#include <string_view>

#include <sal/types.h>
#include <rtl/ustring.hxx>

#if !defined WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <objidl.h>

// target device and formatetc helper
void DeleteTargetDevice(DVTARGETDEVICE* ptd);
bool CopyFormatEtc(LPFORMATETC petcDest, LPFORMATETC petcSrc);
sal_Int32 CompareFormatEtc(const FORMATETC* pFetcLeft, const FORMATETC* pFetcRight);
bool CompareTargetDevice(DVTARGETDEVICE* ptdLeft, DVTARGETDEVICE const* ptdRight);
DVTARGETDEVICE* CopyTargetDevice(DVTARGETDEVICE* ptdSrc);

// some codepage helper functions

// returns a windows codepage appropriate to the
// given mime charset parameter value

sal_uInt32 getWinCPFromMimeCharset(const OUString& charset);

// returns a windows codepage appropriate to the
// given locale and locale type

OUString getWinCPFromLocaleId(LCID lcid, LCTYPE lctype);

// returns a mime charset parameter value appropriate
// to the given codepage, optional a prefix can be
// given, e.g. "windows-" or "cp"

OUString getMimeCharsetFromWinCP(sal_uInt32 cp, std::u16string_view aPrefix);

// returns a mime charset parameter value appropriate
// to the given locale id and locale type, optional a
// prefix can be given, e.g. "windows-" or "cp"

OUString getMimeCharsetFromLocaleId(LCID lcid, LCTYPE lctype, std::u16string_view aPrefix);

// returns true, if a given codepage is an oem codepage

bool IsOEMCP(sal_uInt32 codepage);

// converts a codepage into a string representation

OUString cptostr(sal_uInt32 codepage);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
