/* comment */#pragma once
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <com/sun/star/datatransfer/dnd/XDropTarget.hpp>
#include <com/sun/star/datatransfer/dnd/XDragSource.hpp>
#include <com/sun/star/datatransfer/XTransferable.hpp>
#include <com/sun/star/uno/Reference.h>
#include "../../source/inc/DtObjFactory.hxx"

using namespace com::sun::star::uno;
using namespace com::sun::star::datatransfer::dnd;
using namespace com::sun::star::datatransfer;

struct ThreadData
{
    Reference<XDragSource> source;
    Reference<XTransferable> transferable;
    HANDLE evtThreadReady;
};

class AWindow: public CWindowImpl<AWindow, CWindow,
      CWinTraits<WS_CAPTION |WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0> >
{
    TCHAR m_strName[80];
    Reference<XDropTarget> m_xDropTarget;
    Reference<XDragSource> m_xDragSource;
    BOOL m_isMTA;

    HWND m_hwndEdit;

public:
    explicit AWindow(LPCTSTR strName)
    {
        RECT rcPos= {0,0,200,200};
        Create(0, rcPos, strName);
    }
    AWindow(LPCTSTR strName, RECT pos, BOOL mta=FALSE): m_isMTA( mta)
    {
        Create(0, pos, strName);
    }

    ~AWindow()
    {
        if(m_hWnd)
            DestroyWindow();
    }

    BEGIN_MSG_MAP(AWindow)
        MESSAGE_HANDLER( WM_CLOSE, OnClose)
        MESSAGE_HANDLER( WM_CREATE, OnCreate)
        MESSAGE_RANGE_HANDLER( WM_MOUSEFIRST,  WM_MOUSELAST, OnMouseAction)
        MESSAGE_HANDLER( WM_TIMER, OnTimer)
        MESSAGE_HANDLER( WM_SIZE, OnSize)
        MESSAGE_HANDLER( WM_SETFOCUS, OnFocus)

    END_MSG_MAP()

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseAction(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
