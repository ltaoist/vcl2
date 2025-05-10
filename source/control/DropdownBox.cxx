/* comment */
#include <vcl/toolkit/button.hxx>
#include <vcl/layout.hxx>
#include <DropdownBox.hxx>

#define NOTEBOOK_HEADER_HEIGHT 30

/*
 * DropdownBox - shows content or moves it to the popup
 * which can be opened by clicking on a button
 */

DropdownBox::DropdownBox(vcl::Window* pParent)
    : VclHBox(pParent)
    , m_bInFullView(true)
{
    m_pButton = VclPtr<PushButton>::Create(this, WB_FLATBUTTON);
    m_pButton->SetClickHdl(LINK(this, DropdownBox, PBClickHdl));
    m_pButton->SetSymbol(SymbolType::MENU);
    m_pButton->set_width_request(15);
    m_pButton->SetQuickHelpText(GetQuickHelpText());
    m_pButton->Resize();
}

DropdownBox::~DropdownBox() { disposeOnce(); }

void DropdownBox::dispose()
{
    m_pButton.disposeAndClear();
    if (m_pPopup)
        m_pPopup.disposeAndClear();

    VclHBox::dispose();
}

void DropdownBox::HideContent()
{
    if (m_bInFullView)
    {
        m_bInFullView = false;

        for (int i = 0; i < GetChildCount(); i++)
            GetChild(i)->Hide();

        m_pButton->Show();
        SetOutputSizePixel(Size(m_pButton->GetSizePixel().Width(), GetSizePixel().Height()));
    }
}

bool DropdownBox::IsHidden() { return !m_bInFullView; }

void DropdownBox::ShowContent()
{
    if (!m_bInFullView)
    {
        m_bInFullView = true;

        for (int i = 0; i < GetChildCount(); i++)
            GetChild(i)->Show();

        m_pButton->Hide();
    }
}

IMPL_LINK(DropdownBox, PBClickHdl, Button*, /*pButton*/, void)
{
    if (m_pPopup)
        m_pPopup.disposeAndClear();

    m_pPopup = VclPtr<NotebookbarPopup>::Create(this);

    for (int i = 0; i < GetChildCount(); i++)
    {
        if (GetChild(i) != m_pButton)
        {
            Window* pChild = GetChild(i);
            pChild->Show();

            pChild->SetParent(m_pPopup->getBox());
            // count is decreased because we moved child
            i--;
        }
    }

    m_pPopup->hideSeparators(true);

    m_pPopup->getBox()->set_height_request(GetSizePixel().Height());

    tools::Long x = GetPosPixel().getX();
    tools::Long y = GetPosPixel().getY() + NOTEBOOK_HEADER_HEIGHT + GetSizePixel().Height();
    tools::Rectangle aRect(x, y, x, y);

    m_pPopup->StartPopupMode(aRect, FloatWinPopupFlags::Down | FloatWinPopupFlags::GrabFocus
                                        | FloatWinPopupFlags::AllMouseButtonClose);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
