/* comment */
#pragma once

#include <memory>
#include <string_view>

#include <vcl/dllapi.h>
#include <vcl/toolkit/ivctrl.hxx>
#include <vcl/layout.hxx>

struct VerticalTabPageData;

class VerticalTabControl final : public VclHBox
{
    VclPtr<SvtIconChoiceCtrl> m_xChooser;
    VclPtr<VclVBox> m_xBox;

    std::vector<std::unique_ptr<VerticalTabPageData>> maPageList;
    OString m_sCurrentPageId;

    Link<VerticalTabControl*, void> m_aActivateHdl;
    Link<VerticalTabControl*, bool> m_aDeactivateHdl;

    DECL_LINK(ChosePageHdl_Impl, SvtIconChoiceCtrl*, void);

    void ActivatePage();
    bool DeactivatePage();

    VerticalTabPageData* GetPageData(std::string_view rId) const;
    VerticalTabPageData* GetPageData(const SvxIconChoiceCtrlEntry* pEntry) const;

public:
    VerticalTabControl(vcl::Window* pParent);
    virtual ~VerticalTabControl() override;
    virtual void dispose() override;

    sal_uInt16 GetPageCount() const { return m_xChooser->GetEntryCount(); }

    const OString& GetCurPageId() const { return m_sCurrentPageId; }
    void SetCurPageId(const OString& rId);

    sal_uInt16 GetPagePos(std::string_view rPageId) const;
    const OString& GetPageId(sal_uInt16 nIndex) const;
    VclPtr<vcl::Window> GetPage(std::string_view rPageId) const;

    void RemovePage(std::string_view rPageId);
    void InsertPage(const OString& rPageId, const OUString& rLabel, const Image& rImage,
                    const OUString& rTooltip, VclPtr<vcl::Window> xPage, int nPos = -1);

    void SetActivatePageHdl(const Link<VerticalTabControl*, void>& rLink)
    {
        m_aActivateHdl = rLink;
    }
    void SetDeactivatePageHdl(const Link<VerticalTabControl*, bool>& rLink)
    {
        m_aDeactivateHdl = rLink;
    }

    OUString GetPageText(std::string_view rPageId) const;
    void SetPageText(std::string_view rPageId, const OUString& rText);

    vcl::Window* GetPageParent() { return m_xBox.get(); }

    virtual FactoryFunction GetUITestFactory() const override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
