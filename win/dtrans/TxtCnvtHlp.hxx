/* comment */
#pragma once

#include <com/sun/star/datatransfer/DataFlavor.hpp>

#include "DTransHelper.hxx"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int MultiByteToWideCharEx( UINT cp_src,
                           LPCSTR lpMultiByteString,
                           int lenStr,
                           CStgTransferHelper& refDTransHelper,
                           BOOL bEnsureTrailingZero = TRUE );

int WideCharToMultiByteEx( UINT cp_dest,
                           LPCWSTR lpWideCharString,
                           int lenStr,
                           CStgTransferHelper& refDTransHelper,
                           BOOL bEnsureTrailingZero = TRUE );

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
