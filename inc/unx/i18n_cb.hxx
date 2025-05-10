/* comment */#ifndef INCLUDED_VCL_INC_UNX_I18N_CB_HXX
#define INCLUDED_VCL_INC_UNX_I18N_CB_HXX

#include <X11/Xlib.h>

#include <salwtype.hxx>
#include <vector>

extern "C" {

// xim callbacks
void PreeditDoneCallback ( XIC ic, XPointer client_data, XPointer call_data);
int  PreeditStartCallback( XIC ic, XPointer client_data, XPointer call_data);
void PreeditDrawCallback ( XIC ic, XPointer client_data,
                           XIMPreeditDrawCallbackStruct *call_data );
void PreeditCaretCallback( XIC ic, XPointer client_data,
                           XIMPreeditCaretCallbackStruct *call_data );
void GetPreeditSpotLocation(XIC ic, XPointer client_data);

void StatusStartCallback (XIC ic, XPointer client_data, XPointer call_data);
void StatusDoneCallback  (XIC ic, XPointer client_data, XPointer call_data);
void StatusDrawCallback  (XIC ic, XPointer client_data,
            XIMStatusDrawCallbackStruct *call_data);

// keep informed if kinput2 crashed again
void IC_IMDestroyCallback (XIM im, XPointer client_data, XPointer call_data);
void IM_IMDestroyCallback (XIM im, XPointer client_data, XPointer call_data);

Bool IsControlCode(sal_Unicode nChar);

} /* extern "C" */

struct preedit_text_t
{
    sal_Unicode   *pUnicodeBuffer;
    XIMFeedback   *pCharStyle;
    unsigned int   nLength;
    unsigned int   nSize;
    preedit_text_t()
        : pUnicodeBuffer(nullptr)
        , pCharStyle(nullptr)
        , nLength(0)
        , nSize(0)
    {
    }
};

class SalFrame;

enum class PreeditStatus {
    DontKnow = 0,
    Active,
    ActivationRequired,
    StartPending
};

struct preedit_data_t
{
    SalFrame*               pFrame;
    PreeditStatus           eState;
    preedit_text_t          aText;
    SalExtTextInputEvent    aInputEv;
    std::vector< ExtTextInputAttr >   aInputFlags;
    preedit_data_t()
        : pFrame(nullptr)
        , eState(PreeditStatus::DontKnow)
    {
    }
};

#endif // INCLUDED_VCL_INC_UNX_I18N_CB_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
