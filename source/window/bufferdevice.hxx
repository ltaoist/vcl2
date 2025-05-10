/* comment */

#pragma once

#include <vcl/virdev.hxx>
#include <vcl/window.hxx>

namespace vcl
{
/// Buffers drawing on a vcl::RenderContext using a VirtualDevice.
class VCL_DLLPUBLIC BufferDevice
{
    ScopedVclPtr<VirtualDevice> m_pBuffer;
    VclPtr<vcl::Window> m_pWindow;
    vcl::RenderContext& m_rRenderContext;
    bool m_bDisposed = false;

public:
    BufferDevice(const VclPtr<vcl::Window>& pWindow, vcl::RenderContext& rRenderContext);
    ~BufferDevice();
    void Dispose();

    vcl::RenderContext* operator->();
    vcl::RenderContext& operator*();
};
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
