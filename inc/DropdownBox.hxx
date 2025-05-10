/* comment */
#ifndef INCLUDED_SFX2_NOTEBOOKBAR_DROPDOWNBOX_HXX
#define INCLUDED_SFX2_NOTEBOOKBAR_DROPDOWNBOX_HXX

#include <vcl/layout.hxx>
#include "IPrioritable.hxx"
#include "NotebookbarPopup.hxx"

class DropdownBox final : public VclHBox, public vcl::IPrioritable
{
private:
    bool m_bInFullView;
    VclPtr<PushButton> m_pButton;
    VclPtr<NotebookbarPopup> m_pPopup;

public:
    explicit DropdownBox(vcl::Window* pParent);
    virtual ~DropdownBox() override;
    virtual void dispose() override;

    void HideContent() override;
    void ShowContent() override;
    bool IsHidden() override;

private:
    DECL_LINK(PBClickHdl, Button*, void);
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
