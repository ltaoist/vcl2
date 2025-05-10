/* comment */
#pragma once

#include <svimpbox.hxx>

class SvTreeListBox;
class Point;

class IconViewImpl : public SvImpLBox
{
public:
    IconViewImpl(SvTreeListBox* pTreeListBox, SvTreeList* pTreeList, WinBits nWinStyle);

    void KeyDown(bool bPageDown) override;

    void KeyUp(bool bPageUp) override;

    Point GetEntryPosition(const SvTreeListEntry* pEntry) const override;

    SvTreeListEntry* GetClickedEntry(const Point& rPoint) const override;

    bool IsEntryInView(SvTreeListEntry* pEntry) const override;

    void Paint(vcl::RenderContext& rRenderContext, const tools::Rectangle& rRect) override;

    // returns 0 if position is just past the last entry
    SvTreeListEntry* GetEntry(const Point& rPoint) const override;

    void UpdateAll(bool bInvalidateCompleteView) override;

    bool KeyInput(const KeyEvent&) override;

    void InvalidateEntry(tools::Long nId) const override;

protected:
    tools::Long GetEntryLine(const SvTreeListEntry* pEntry) const override;

    void CursorUp() override;
    void CursorDown() override;
    void PageDown(sal_uInt16 nDelta) override;
    void PageUp(sal_uInt16 nDelta) override;

    void SyncVerThumb() override;
    void AdjustScrollBars(Size& rSize) override;

private:
    enum class CallbackResult
    {
        Continue,
        Stop, // Stop iteration
    };
    struct EntryAreaInfo
    {
        SvTreeListEntry* entry;
        short column;
        tools::Rectangle area; // The area for the entry
    };
    using IterateEntriesFunc = std::function<CallbackResult(const EntryAreaInfo&)>;

    void IterateVisibleEntryAreas(const IterateEntriesFunc& f, bool fromStartEntry = false) const;

    Size GetEntrySize(const SvTreeListEntry& entry) const;
    // Get first entry at most n rows above; nullptr if no rows above
    SvTreeListEntry* GoToPrevRow(SvTreeListEntry* pEntry, int n) const;
    // Get first entry at most n rows below; nullptr if no rows below
    SvTreeListEntry* GoToNextRow(SvTreeListEntry* pEntry, int n) const;

    tools::Long GetEntryRow(const SvTreeListEntry* entry) const;
    void SetStartEntry(SvTreeListEntry* entry);
    void ScrollTo(SvTreeListEntry* entry);
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
