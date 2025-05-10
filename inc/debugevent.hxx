/* comment */

#ifndef INCLUDED_VCL_DEBUGEVENT_HXX
#define INCLUDED_VCL_DEBUGEVENT_HXX

#include <vcl/dllapi.h>
#include <vcl/timer.hxx>
#include <sal/types.h>

namespace vcl { class Window; }

class DebugEventInjector final : private Timer {
  sal_uInt32 mnEventsLeft;
  DebugEventInjector( sal_uInt32 nMaxEvents );

  static vcl::Window *ChooseWindow();
  static void InjectTextEvent();
  static void InjectMenuEvent();
  static void InjectEvent();
  static void InjectKeyNavEdit();
  virtual void Invoke() override;

  public:
     static DebugEventInjector *getCreate();
};

#endif // INCLUDED_VCL_DEBUGEVENT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
