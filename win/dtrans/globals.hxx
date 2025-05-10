/* comment */#pragma once

#include <sal/config.h>

#include <com/sun/star/uno/Reference.hxx>
#include <osl/mutex.hxx>

namespace com::sun::star::datatransfer
{
class XTransferable;
}

#include <wtypes.h>
#include <sal/types.h>

// This maps key states as occur as parameter, e.g. in IDropTarget::DragEnter,
// IDropSource::QueryContinueDrag, to actions as are declared in
// css::datatransfer::dnd::DNDConstants ( ACTION_MOVE etc).
// If the grfKeyState indicates the ALt or right mousebutton then the returned
// values combines all possible actions. This is because those keys and buttons are
// used when the user expect a menu to appear when he drops. The menu then
// contains entries, such as move, copy, link, cancel.
// An odd fact is that the argument grfKeyState in IDropTarget::Drop does not
// contain mouse buttons (winnt 4 SP6). That indicates that the right mouse button
// is not considered relevant in a drag operation. Contrarily the file explorer
// gives that button a special meaning: the user has to select the effect from
// a context menu on drop.
sal_Int8 dndOleKeysToAction(DWORD grfKeyState, sal_Int8 sourceActions);

// The function maps a windows DROPEFFECTs to actions
// ( css::datatransfer::dnd::DNDConstants).
// The argument can be a combination of different DROPEFFECTS,
// In that case the return value is also a combination of the
// appropriate actions.
sal_Int8 dndOleDropEffectsToActions(DWORD dwEffect);

// The function maps actions ( css::datatransfer::dnd::DNDConstants)
// to window DROPEFFECTs.
// The argument can be a combination of different actions
// In that case the return value is also a combination of the
// appropriate DROPEFFECTS.
DWORD dndActionsToDropEffects(sal_Int8 actions);

// If the argument constitutes only one action then it is mapped to the
// corresponding DROPEFFECT otherwise DROPEFFECT_MOVE is returned. This is
// why move is the default effect (no modifiers pressed, or right mouse button
// or Alt).
DWORD dndActionsToSingleDropEffect(sal_Int8 actions);

extern css::uno::Reference<css::datatransfer::XTransferable> g_XTransferable;

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
