/* comment */
#include <vcl/toolkit/viewdataentry.hxx>

SvViewDataEntry::SvViewDataEntry() :
    nVisPos(0),
    mbSelected(false),
    mbHighlighted(false),
    mbExpanded(false),
    mbFocused(false),
    mbSelectable(true),
    mbDragTarget(false)
{
}

SvViewDataEntry::SvViewDataEntry( const SvViewDataEntry& rData ) :
    nVisPos(rData.nVisPos),
    mbSelected(false),
    mbHighlighted(false),
    mbExpanded(rData.mbExpanded),
    mbFocused(false),
    mbSelectable(rData.mbSelectable),
    mbDragTarget(false)
{
}

SvViewDataEntry::~SvViewDataEntry()
{
#ifdef DBG_UTIL
    nVisPos = 0x12345678;
#endif
}

void SvViewDataEntry::SetFocus( bool bFocus )
{
    mbFocused = bFocus;
}

void SvViewDataEntry::SetSelected( bool bSelected )
{
    mbSelected = bSelected;
    mbHighlighted = bSelected;
}

void SvViewDataEntry::SetExpanded( bool bExpanded )
{
    mbExpanded = bExpanded;
}

void SvViewDataEntry::SetSelectable( bool bSelectable )
{
    mbSelectable = bSelectable;
}

void SvViewDataEntry::Init(size_t nSize)
{
    maItems.resize(nSize);
}

const SvViewDataItem& SvViewDataEntry::GetItem(size_t nPos) const
{
    return maItems[nPos];
}

SvViewDataItem& SvViewDataEntry::GetItem(size_t nPos)
{
    return maItems[nPos];
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
