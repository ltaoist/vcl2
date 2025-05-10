/* comment */
#pragma once

#include <config_options.h>
#include <tools/solar.h>
#include <tools/link.hxx>
#include <vcl/keycod.hxx>
#include <vcl/dllapi.h>
#include <memory>
#include <map>
#include <vector>

class CommandEvent;

class Accelerator;

class ImplAccelEntry
{
public:
    Accelerator*    mpAccel;
    Accelerator*    mpAutoAccel;
    vcl::KeyCode    maKeyCode;
    sal_uInt16      mnId;
    bool            mbEnabled;
};

typedef ::std::vector< std::unique_ptr<ImplAccelEntry> > ImplAccelList;

class Accelerator
{
    friend class ImplAccelManager;

private:
    typedef ::std::map< sal_uLong, ImplAccelEntry* > ImplAccelMap;
    ImplAccelMap  maKeyMap; // for keycodes, generated with a code
    ImplAccelList maIdList; // Id-List
    Link<Accelerator&,void> maActivateHdl;
    Link<Accelerator&,void> maSelectHdl;

    // Will be set by AcceleratorManager
    sal_uInt16              mnCurId;
    bool*                   mpDel;

    void    ImplInit();
    void    ImplCopyData( const Accelerator& rAccelData );
    void    ImplDeleteData();
    void    ImplInsertAccel(sal_uInt16 nItemId, const vcl::KeyCode& rKeyCode,
                            bool bEnable, Accelerator* pAutoAccel);

    ImplAccelEntry*         ImplGetAccelData( const vcl::KeyCode& rKeyCode ) const;

public:
                            Accelerator();
                            Accelerator( const Accelerator& rAccel );
                            ~Accelerator();

    void                    Activate();
    void                    Select();

    void                    InsertItem( sal_uInt16 nItemId, const vcl::KeyCode& rKeyCode );

    sal_uInt16              GetCurItemId() const { return mnCurId; }

    sal_uInt16              GetItemCount() const;
    sal_uInt16              GetItemId( sal_uInt16 nPos ) const;

    Accelerator*            GetAccel( sal_uInt16 nItemId ) const;

    void                    SetActivateHdl( const Link<Accelerator&,void>& rLink ) { maActivateHdl = rLink; }
    void                    SetSelectHdl( const Link<Accelerator&,void>& rLink ) { maSelectHdl = rLink; }

    Accelerator&            operator=( const Accelerator& rAccel );
};

bool ImplGetKeyCode( KeyFuncType eFunc, sal_uInt16& rCode1, sal_uInt16& rCode2, sal_uInt16& rCode3, sal_uInt16& rCode4 );

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
