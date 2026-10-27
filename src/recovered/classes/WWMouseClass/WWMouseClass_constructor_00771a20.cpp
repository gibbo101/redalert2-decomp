// WWMouseClass::WWMouseClass(Surface *surface, HWND window) (0x00771A20)
// Empty state, hidden; confines the mouse to the window's client area, makes
// itself the thread's mouse and hides the Windows cursor.
// Unresolved: why the hotspot starts at the centre of the client area.
#include "shared/wwmouse.hpp"
// @ref ??_7Mouse@@6B@=007afc38
// @ref ??_7WWMouseClass@@6B@=007afbec
// @ref _unknown_empty_rect=00b2af20
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?_Mouse@@3PAVWWMouseClass@@A=00b2af5c
// @ref ?Calc_Confining_Rect@WWMouseClass@@QAEXXZ=00771c50
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

WWMouseClass::WWMouseClass(Surface *surface, HWND window)
    : MouseCursor(0),
      MouseFrame(0),
      MouseState(-1),
      IsCaptured(false),
      DrawX(0),
      DrawY(0),
      MouseX(0),
      MouseY(0),
      ScreenSurface(surface),
      Window(window),
      ConfiningRect(unknown_empty_rect),
      HotspotX(0),
      HotspotY(0),
      Background(0),
      BackgroundRect(unknown_empty_rect),
      SurfaceBackground(0),
      SurfaceBackgroundRect(unknown_empty_rect),
      SidebarBackground(0),
      SidebarBackgroundRect(unknown_empty_rect),
      unknown_80(unknown_empty_rect),
      unknown_90(-1),
      unknown_94(0)
{
    Block_Mouse();
    Calc_Confining_Rect();
    HotspotX = ConfiningRect.X + ConfiningRect.Width / 2;
    HotspotY = ConfiningRect.Y + ConfiningRect.Height / 2;
    _Mouse = this;
    Unblock_Mouse();
    ShowCursor(0);
}
