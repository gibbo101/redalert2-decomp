// void ScrollClass::Unknown_0066A290() (0x0066A290)
#include "shared/scroll.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/planning_mouse.hpp"
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Planning_Mouse_Move_00617900@@YG_NHH@Z=00617900
// @ref ?Down@WWKeyboardClass@@QAE_NH@Z=00532890
// @ref ?unknown_slot47@DisplayClass@@UAEXABUPoint2D@@@Z=0049c500
// @ref ?Unknown_0066A7A0@ScrollClass@@QAEXABUPoint2D@@@Z=0066a7a0
// @ref ?Unknown_00669650@ScrollClass@@QAE_NABUPoint2D@@AAVCell@@AAUCoordStruct@@AAPAVObjectClass@@AA_N4@Z=00669650
// @ref ?Unknown_00669960@ScrollClass@@QAEHABVCell@@PAVObjectClass@@_N@Z=00669960
// @ref ?unknown_slot46@DisplayClass@@UAEXABVCell@@_NPAVObjectClass@@H1@Z=0049b0f0
// @ref ?Edge_Scroll_00669EC0@ScrollClass@@QAEXABUPoint2D@@@Z=00669ec0

void ScrollClass::Unknown_0066A290()
{
    if (unknown_flag_a40d44) {
        return;
    }
    int x = unknown_rect_839630.X;
    int y = unknown_rect_839630.Y;
    Point2D mouse = WWMouse->Get_Mouse_XY();
    Point2D xy(mouse.X - x, mouse.Y - y);
    if (Planning_Mouse_Move_00617900(xy.X, xy.Y)) {
        return;
    }
    if (unknown_4f2a == true) {
        if (WWKeyboard->Down(1)) {
            Map.unknown_slot47(xy);
        } else if (WWKeyboard->Down(2)) {
            Map.Unknown_0066A7A0(xy);
        }
    } else {
        Cell cell;
        CoordStruct coord;
        ObjectClass *object;
        bool arg5;
        bool arg6;
        if (Unknown_00669650(xy, cell, coord, object, arg5, arg6)) {
            Map.unknown_slot46(cell, arg6, object, Unknown_00669960(cell, object, true), false);
        }
        if (unknown_4f29 && !unknown_a40d13) {
            Edge_Scroll_00669EC0(xy);
        }
    }
}
