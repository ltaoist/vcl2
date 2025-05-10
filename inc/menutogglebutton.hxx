/* comment */
#pragma once

#include <vcl/toolkit/menubtn.hxx>

class MenuToggleButton final : public MenuButton
{
public:
    explicit MenuToggleButton(vcl::Window* pParent, WinBits nStyle);
    virtual ~MenuToggleButton() override;

    void SetActive(bool bSel);
    bool GetActive() const;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
