/* comment */
#ifndef INCLUDED_VCL_INC_HELPWIN_HXX
#define INCLUDED_VCL_INC_HELPWIN_HXX

#include <vcl/toolkit/floatwin.hxx>
#include <vcl/timer.hxx>

enum class QuickHelpFlags;
struct ImplSVHelpData;

/// A tooltip: adds tips to widgets in a floating / popup window.
class HelpTextWindow final : public FloatingWindow
{
private:
    tools::Rectangle           maHelpArea; // If next Help for the same rectangle w/ same text, then keep window

    tools::Rectangle           maTextRect; // For wrapped text in QuickHelp

    OUString            maHelpText;

    Timer               maShowTimer;
    Timer               maHideTimer;

    sal_uInt16          mnHelpWinStyle;
    QuickHelpFlags      mnStyle;

private:
    DECL_LINK( TimerHdl, Timer*, void );

    virtual void Paint(vcl::RenderContext& rRenderContext, const tools::Rectangle&) override;
    virtual void RequestHelp( const HelpEvent& rHEvt ) override;
    virtual void ApplySettings(vcl::RenderContext& rRenderContext) override;

    virtual OUString GetText() const override;
    void ImplShow();

    virtual void        dispose() override;
public:
                        HelpTextWindow( vcl::Window* pParent, const OUString& rText, sal_uInt16 nHelpWinStyle, QuickHelpFlags nStyle );
    virtual             ~HelpTextWindow() override;

    const OUString&     GetHelpText() const { return maHelpText; }
    void                SetHelpText( const OUString& rHelpText );
    sal_uInt16          GetWinStyle() const { return mnHelpWinStyle; }
    QuickHelpFlags      GetStyle() const { return mnStyle; }

    // only remember:
    void                SetHelpArea( const tools::Rectangle& rRect ) { maHelpArea = rRect; }

    void                ShowHelp(bool bNoDelay);

    Size                CalcOutSize() const;
    const tools::Rectangle&    GetHelpArea() const { return maHelpArea; }
};

void ImplShowHelpWindow( vcl::Window* pParent, sal_uInt16 nHelpWinStyle, QuickHelpFlags nStyle,
        const OUString& rHelpText,
        const Point& rScreenPos, const tools::Rectangle& rHelpArea );
VCL_DLLPUBLIC void ImplDestroyHelpWindow( bool bUpdateHideTime );
void ImplDestroyHelpWindow(ImplSVHelpData& rHelpData, bool bUpdateHideTime);
void ImplSetHelpWindowPos( vcl::Window* pHelpWindow, sal_uInt16 nHelpWinStyle, QuickHelpFlags nStyle,
                            const Point& rPos, const tools::Rectangle& rHelpArea );

#endif // INCLUDED_VCL_INC_HELPWIN_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
