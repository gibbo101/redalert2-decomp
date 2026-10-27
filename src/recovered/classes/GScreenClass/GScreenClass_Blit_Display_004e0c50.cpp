// void GScreenClass::Blit_Display() (0x004E0C50, slot 17)
// Flushes the 3D device (an empty scene) when it is in use, then copies the
// composed surface to the screen without the mouse.
#include "shared/gscreen.hpp"
// @ref ?unknown_flag_852fd7@@3_NA=00852fd7
// @ref ?unknown_device_852fe0@@3PAUIDirect3DDevice2@@A=00852fe0
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90

void GScreenClass::Blit_Display()
{
    if (unknown_flag_852fd7 && unknown_device_852fe0->BeginScene() == 0) {
        unknown_device_852fe0->EndScene();
    }
    Blit(false, unknown_surface_839964);
}
