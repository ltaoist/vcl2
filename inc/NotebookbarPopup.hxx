/* comment */
#ifndef INCLUDED_SFX2_NOTEBOOKBAR_NOTEBOOKBARPOPUP_HXX
#define INCLUDED_SFX2_NOTEBOOKBAR_NOTEBOOKBARPOPUP_HXX

#include <vcl/layout.hxx>
#include <vcl/toolkit/floatwin.hxx>

/*
 * Popup - shows hidden content, controls are moved to this popup
 * and after close moved to the original parent
 */

class NotebookbarPopup final : public FloatingWindow
{
private:
    VclPtr<VclHBox> m_pBox;
    ScopedVclPtr<VclHBox> m_pParent;

public:
    explicit NotebookbarPopup(const VclPtr<VclHBox>& pParent);

    virtual ~NotebookbarPopup() override;

    VclHBox* getBox();

    virtual void PopupModeEnd() override;

    void hideSeparators(bool bHide);

    void dispose() override;

    void ApplyBackground(vcl::Window* pWindow);

    void RemoveBackground(vcl::Window* pWindow);
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
