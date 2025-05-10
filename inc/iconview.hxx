/* comment */
#ifndef INCLUDED_SVTOOLS_ICONVIEW_HXX
#define INCLUDED_SVTOOLS_ICONVIEW_HXX

#include <vcl/toolkit/treelistbox.hxx>

class IconView final : public SvTreeListBox
{
public:
    IconView(vcl::Window* pParent, WinBits nBits);

    Size GetEntrySize(const SvTreeListEntry&) const;

    virtual void Resize() override;

    virtual tools::Rectangle GetFocusRect(const SvTreeListEntry*, tools::Long) override;

    void PaintEntry(SvTreeListEntry&, tools::Long nX, tools::Long nY,
                    vcl::RenderContext& rRenderContext);

    virtual css::uno::Reference<css::accessibility::XAccessible> CreateAccessible() override;

    virtual OUString GetEntryAccessibleDescription(SvTreeListEntry* pEntry) const override;
    void SetEntryAccessibleDescriptionHdl(const Link<SvTreeListEntry*, OUString>& rLink)
    {
        maEntryAccessibleDescriptionHdl = rLink;
    }

    virtual FactoryFunction GetUITestFactory() const override;
    virtual void DumpAsPropertyTree(tools::JsonWriter& rJsonWriter) override;

protected:
    virtual void CalcEntryHeight(SvTreeListEntry const* pEntry) override;

private:
    Link<SvTreeListEntry*, OUString> maEntryAccessibleDescriptionHdl;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
