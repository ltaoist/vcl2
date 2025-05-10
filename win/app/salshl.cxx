/* comment */
#include <svsys.h>
#include <sal/log.hxx>
#include <win/saldata.hxx>

SalShlData aSalShlData;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInst, DWORD nReason, LPVOID)
{
    if ( nReason == DLL_PROCESS_ATTACH )
        aSalShlData.mhInst = hInst;
    return 1;
}

HCURSOR ImplLoadSalCursor( int nId )
{
    SAL_WARN_IF( !aSalShlData.mhInst, "vcl", "no DLL instance handle" );

    HCURSOR hCursor = LoadCursorW( aSalShlData.mhInst, MAKEINTRESOURCEW( nId ) );

    SAL_WARN_IF( !hCursor, "vcl", "cursor not found in sal resource" );

    return hCursor;
}

HBITMAP ImplLoadSalBitmap( int nId )
{
    SAL_WARN_IF( !aSalShlData.mhInst, "vcl", "no DLL instance handle" );

    HBITMAP hBitmap = LoadBitmapW( aSalShlData.mhInst, MAKEINTRESOURCEW( nId ) );

    SAL_WARN_IF( !hBitmap, "vcl", "bitmap not found in sal resource" );

    return hBitmap;
}

bool ImplLoadSalIcon( int nId, HICON& rIcon, HICON& rSmallIcon )
{
    SAL_WARN_IF( !aSalShlData.mhInst, "vcl", "no DLL instance handle" );

    SalData* pSalData = GetSalData();

    // check the cache first
    SalIcon *pSalIcon = pSalData->mpFirstIcon;
    while( pSalIcon )
    {
        if( pSalIcon->nId != nId )
            pSalIcon = pSalIcon->pNext;
        else
        {
            rIcon       = pSalIcon->hIcon;
            rSmallIcon  = pSalIcon->hSmallIcon;
            return (rSmallIcon != nullptr);
        }
    }

    // Try at first to load the icons from the application exe file
    rIcon = static_cast<HICON>(LoadImageW( pSalData->mhInst, MAKEINTRESOURCEW( nId ),
                                           IMAGE_ICON, GetSystemMetrics( SM_CXICON ), GetSystemMetrics( SM_CYICON ),
                                           LR_DEFAULTCOLOR ));
    if ( !rIcon )
    {
        // If the application don't provide these icons, then we try
        // to load the icon from the VCL resource
        rIcon = static_cast<HICON>(LoadImageW( aSalShlData.mhInst, MAKEINTRESOURCEW( nId ),
                                           IMAGE_ICON, GetSystemMetrics( SM_CXICON ), GetSystemMetrics( SM_CYICON ),
                                           LR_DEFAULTCOLOR ));
        if ( rIcon )
        {
            rSmallIcon = static_cast<HICON>(LoadImageW( aSalShlData.mhInst, MAKEINTRESOURCEW( nId ),
                                           IMAGE_ICON, GetSystemMetrics( SM_CXSMICON ), GetSystemMetrics( SM_CYSMICON ),
                                           LR_DEFAULTCOLOR ));
        }
        else
            rSmallIcon = nullptr;
    }
    else
    {
        rSmallIcon = static_cast<HICON>(LoadImageW( pSalData->mhInst, MAKEINTRESOURCEW( nId ),
                                       IMAGE_ICON, GetSystemMetrics( SM_CXSMICON ), GetSystemMetrics( SM_CYSMICON ),
                                       LR_DEFAULTCOLOR ));
    }

    if( rIcon )
    {
        // add to icon cache
        pSalData->mpFirstIcon = new SalIcon{
            nId, rIcon, rSmallIcon, pSalData->mpFirstIcon};
    }

    return (rSmallIcon != nullptr);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
