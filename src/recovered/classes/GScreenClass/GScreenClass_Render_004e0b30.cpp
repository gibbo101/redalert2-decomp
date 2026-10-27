// void GScreenClass::Render() (0x004E0B30, slot 15)
// Composes the frame on the 0x00839964 surface (mouse removed): the three
// tactical passes around Draw_It, the buttons and the overlays, then puts
// the mouse back and blits the result.
#include "shared/gscreen.hpp"
#include "shared/tool_tip.hpp"
#include "shared/mouse.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Buttons@GScreenClass@@2PAVGadgetClass@@A=00a40eec
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A45A0@Tactical@@QAEXPAVSurface@@_NH@Z=006a45a0
// @ref ?unknown_flag_abcd85@@3_NA=00abcd85
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?unknown_object_a3dc70@@3VUnknownObjectA3DC70@@A=00a3dc70
// @ref ?Unknown_005B5B30@UnknownObjectA3DC70@@QAEXXZ=005b5b30
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?unknown_flag_a3d8c4@@3_NA=00a3d8c4
// @ref ?Unknown_005419E0@@YIX_N@Z=005419e0

void GScreenClass::Render()
{
    Surface *old = unknown_surface_83995c;
    unknown_surface_83995c = unknown_surface_839964;
    WWMouse->Erase_Mouse(unknown_surface_839964, false);

    bool any = IsToRedraw != 0;
    bool complete = IsToRedraw == 2;
    IsToRedraw = 0;
    unknown_tactical_83996c->Unknown_006A45A0(unknown_surface_839964, any, 0);
    unknown_tactical_83996c->Unknown_006A45A0(unknown_surface_839964, any, 1);
    Draw_It(complete);
    unknown_tactical_83996c->Unknown_006A45A0(unknown_surface_839964, any, 2);

    if (unknown_flag_abcd85 && !unknown_flag_a40d13) {
        WWMouse->Erase_Mouse(unknown_surface_839948, true);
        unknown_flag_abcd85 = false;
    }
    if (Buttons != 0) {
        Buttons->Draw_All(false);
    }
    unknown_object_a3dc70.Unknown_005B5B30();
    if (ToolTips != 0) {
        ToolTips->Refresh(false);
    }
    if (unknown_flag_a3d8c4) {
        Unknown_005419E0(false);
    }
    WWMouse->Draw_Mouse(unknown_surface_839964, false);
    Blit_Display();
    unknown_surface_83995c = old;
}
