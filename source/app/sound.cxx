/* comment */
#include <vcl/svapp.hxx>
#include <vcl/window.hxx>
#include <vcl/sound.hxx>

#include <salframe.hxx>
#include <svdata.hxx>

void Sound::Beep()
{
    // #i91990#
    if (Application::IsHeadlessModeEnabled())
        return;

    vcl::Window* pWindow = ImplGetDefaultWindow();

    pWindow->ImplGetFrame()->Beep();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
