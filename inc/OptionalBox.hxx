/* comment */
#pragma once

#include <vcl/layout.hxx>
#include "IPrioritable.hxx"

class OptionalBox final : public VclHBox, public vcl::IPrioritable
{
private:
    bool m_bInFullView;

public:
    explicit OptionalBox(vcl::Window* pParent);
    virtual ~OptionalBox() override;

    void HideContent() override;
    void ShowContent() override;
    bool IsHidden() override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
