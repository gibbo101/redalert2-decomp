// bool WWMouseClass::Validate_Backgrounds() (0x00771F50)
// Replaces save-under surfaces smaller than the cursor shape and creates the
// missing ones in the screen's pixel format; true when all three exist.
// Name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7XSurface@@6B@=0079af8c

bool WWMouseClass::Validate_Backgrounds()
{
    if (Has_Cursor()) {
    if (Background != 0
        && (MouseCursor->Width > Background->Get_Width() || MouseCursor->Height > Background->Get_Height())) {
        delete Background;
        Background = 0;
    }
    if (SurfaceBackground != 0
        && (MouseCursor->Width > SurfaceBackground->Get_Width()
            || MouseCursor->Height > SurfaceBackground->Get_Height())) {
        delete SurfaceBackground;
        SurfaceBackground = 0;
    }
    if (SidebarBackground != 0
        && (MouseCursor->Width > SidebarBackground->Get_Width()
            || MouseCursor->Height > SidebarBackground->Get_Height())) {
        delete SidebarBackground;
        SidebarBackground = 0;
    }
    if (ScreenSurface != 0) {
        if (Background == 0) {
            Background = new BSurface(MouseCursor->Get_Width(), MouseCursor->Get_Height(), ScreenSurface->Bytes_Per_Pixel());
        }
        if (SurfaceBackground == 0) {
            SurfaceBackground
                = new BSurface(MouseCursor->Get_Width(), MouseCursor->Get_Height(), ScreenSurface->Bytes_Per_Pixel());
        }
        if (SidebarBackground == 0) {
            SidebarBackground
                = new BSurface(MouseCursor->Get_Width(), MouseCursor->Get_Height(), ScreenSurface->Bytes_Per_Pixel());
        }
    }
    return Background != 0 && SurfaceBackground != 0 && SidebarBackground != 0;
    }
    return false;
}
