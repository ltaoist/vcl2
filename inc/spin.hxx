/* comment */
#ifndef INCLUDED_VCL_INC_SPIN_HXX
#define INCLUDED_VCL_INC_SPIN_HXX

#include <vcl/window.hxx>

namespace tools { class Rectangle; }

// Draw Spinners as found in a SpinButton. Some themes like gtk3 will draw +- elements here,
// so these are only suitable in the context of SpinButtons
void ImplDrawSpinButton(vcl::RenderContext& rRenderContext, vcl::Window* pWindow,
                        const tools::Rectangle& rUpperRect, const tools::Rectangle& rLowerRect,
                        bool bUpperIn, bool bLowerIn, bool bUpperEnabled = true, bool bLowerEnabled = true,
                        bool bHorz = false, bool bMirrorHorz = false);

// Draw Up/Down buttons suitable for use in any context
void ImplDrawUpDownButtons(vcl::RenderContext& rRenderContext,
                           const tools::Rectangle& rUpperRect, const tools::Rectangle& rLowerRect,
                           bool bUpperIn, bool bLowerIn, bool bUpperEnabled, bool bLowerEnabled,
                           bool bHorz, bool bMirrorHorz = false);


#endif // INCLUDED_VCL_INC_SPIN_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
