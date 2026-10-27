// WWMouseClass::~WWMouseClass() (0x00771BC0)
// Detaches from the mouse thread and deletes the three save-under surfaces.
#include "shared/wwmouse.hpp"
// @ref ??_7Mouse@@6B@=007afc38
// @ref ??_7WWMouseClass@@6B@=007afbec
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?_Mouse@@3PAVWWMouseClass@@A=00b2af5c
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

WWMouseClass::~WWMouseClass()
{
    Block_Mouse();
    if (_Mouse == this) {
        _Mouse = 0;
    }
    Unblock_Mouse();
    if (Background != 0) {
        delete Background;
        Background = 0;
    }
    if (SurfaceBackground != 0) {
        delete SurfaceBackground;
        SurfaceBackground = 0;
    }
    if (SidebarBackground != 0) {
        delete SidebarBackground;
        SidebarBackground = 0;
    }
}
