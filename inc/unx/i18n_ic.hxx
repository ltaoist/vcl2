/* comment */
#ifndef INCLUDED_VCL_INC_UNX_I18N_IC_HXX
#define INCLUDED_VCL_INC_UNX_I18N_IC_HXX

#include "i18n_cb.hxx"

enum class EndExtTextInputFlags;

class SalI18N_InputContext
{

private:

    Bool    mbUseable; // system supports current locale ?
    XIC     maContext;

    XIMStyle mnSupportedPreeditStyle;
    XIMStyle mnStatusStyle;
    XIMStyle mnPreeditStyle;

    preedit_data_t maClientData;
    XIMCallback maPreeditStartCallback;
    XIMCallback maPreeditDoneCallback;
    XIMCallback maPreeditDrawCallback;
    XIMCallback maPreeditCaretCallback;
    XIMCallback maCommitStringCallback;
    XIMCallback maSwitchIMCallback;
    XIMCallback maDestroyCallback;

    XVaNestedList mpAttributes;
    XVaNestedList mpStatusAttributes;
    XVaNestedList mpPreeditAttributes;

    bool         SupportInputMethodStyle( XIMStyles const *pIMStyles );
    static unsigned int GetWeightingOfIMStyle(   XIMStyle n_style );
    bool         IsSupportedIMStyle(      XIMStyle n_style ) const;

public:

    Bool UseContext() const { return mbUseable; }
    bool IsPreeditMode() const { return maClientData.eState == PreeditStatus::Active; }
    XIC  GetContext() const { return maContext; }

    void ExtendEventMask(  ::Window aFocusWindow );
    void SetICFocus( SalFrame* pFocusFrame );
    void UnsetICFocus();
    void HandleDestroyIM();

    void EndExtTextInput();
    void CommitKeyEvent( sal_Unicode const * pText, std::size_t nLength );
    int  UpdateSpotLocation();

    void Map( SalFrame *pFrame );
    void Unmap();

    SalI18N_InputContext( SalFrame *aFrame );
    ~SalI18N_InputContext();
};

#endif // INCLUDED_VCL_INC_UNX_I18N_IC_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
