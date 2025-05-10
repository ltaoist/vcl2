/* comment */
#include <vcl/layout.hxx>
#include <OptionalBox.hxx>

/*
 * OptionalBox - shows or hides the content. To use with PriorityHBox
 * or PriorityMergedHBox
 */

OptionalBox::OptionalBox(vcl::Window* pParent)
    : VclHBox(pParent)
    , m_bInFullView(true)
{
}

OptionalBox::~OptionalBox() { disposeOnce(); }

void OptionalBox::HideContent()
{
    if (m_bInFullView)
    {
        m_bInFullView = false;

        for (int i = 0; i < GetChildCount(); i++)
            GetChild(i)->Hide();

        SetOutputSizePixel(Size(10, GetSizePixel().Height()));
    }
}

void OptionalBox::ShowContent()
{
    if (!m_bInFullView)
    {
        m_bInFullView = true;

        for (int i = 0; i < GetChildCount(); i++)
            GetChild(i)->Show();
    }
}

bool OptionalBox::IsHidden() { return !m_bInFullView; }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
