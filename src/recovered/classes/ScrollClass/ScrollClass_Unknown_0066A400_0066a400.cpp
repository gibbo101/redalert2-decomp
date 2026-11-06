// void ScrollClass::Unknown_0066A400(HWND window, unsigned &message, unsigned &wparam, long &lparam) (0x0066A400)
#include "shared/scroll.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/mouse.hpp"
#include "shared/planning_mouse.hpp"
// @ref ?unknown_flag_a40380@@3_NA=00a40380
// @ref ?unknown_flag_a40d04@@3_NA=00a40d04
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_flag_83740c@@3_NA=0083740c
// @ref __imp__SetCapture@4=0079a3f0
// @ref __imp__ReleaseCapture@0=0079a3e8
// @ref ?Planning_Left_Down_00617340@@YG_NHH@Z=00617340
// @ref ?Planning_Left_Up_00617680@@YG_NUPoint2D@@@Z=00617680
// @ref ?Planning_Mouse_Down@@YGXHH@Z=00617860
// @ref ?Planning_Mouse_Up@@YGXHH@Z=006178a0
// @ref ?Unknown_00669650@ScrollClass@@QAE_NABUPoint2D@@AAVCell@@AAUCoordStruct@@AAPAVObjectClass@@AA_N4@Z=00669650
// @ref ?Unknown_00669960@ScrollClass@@QAEHABVCell@@PAVObjectClass@@_N@Z=00669960
// @ref ?unknown_slot44@DisplayClass@@UAEXABUPoint2D@@@Z=0049af80
// @ref ?unknown_slot45@DisplayClass@@UAEXABUPoint2D@@@Z=0049c490
// @ref ?unknown_slot46@DisplayClass@@UAEXABVCell@@_NPAVObjectClass@@H1@Z=0049b0f0
// @ref ?unknown_slot48@DisplayClass@@UAEXABUCoordStruct@@ABVCell@@PAVObjectClass@@H_N@Z=0049bb20
// @ref ?unknown_slot49@DisplayClass@@UAEXABUPoint2D@@@Z=0049af90
// @ref ?unknown_slot35@DisplayClass@@UAEXXZ=0049ebf0

void ScrollClass::Unknown_0066A400(HWND window, unsigned &message, unsigned &wparam, long &lparam)
{
    if (!unknown_flag_a40380) {
        return;
    }
    if (!unknown_flag_a40d04 && !unknown_a40d13) {
        return;
    }
    if (!unknown_flag_a40958 || unknown_tactical_83996c == 0 || WWMouse == 0) {
        return;
    }
    if (unknown_flag_a40d44 && message != 0x215) {
        return;
    }
    Point2D xy;
    Cell cell;
    CoordStruct coord;
    ObjectClass *object;
    bool arg5;
    bool arg6;
    switch (message) {
    case 0x201: {
        long position = lparam;
        xy.X = ((short *)&position)[0] - unknown_rect_839630.X;
        xy.Y = ((short *)&position)[1] - unknown_rect_839630.Y;
        if (!Unknown_00669650(xy, cell, coord, object, arg5, arg6)) {
            break;
        }
        if (Planning_Left_Down_00617340(xy.X, xy.Y)) {
            break;
        }
        if (unknown_4f2a) {
            break;
        }
        Map.unknown_slot46(cell, arg6, object, Unknown_00669960(cell, object, true), false);
        Map.unknown_slot45(xy);
        SetCapture(MainWindow);
        unknown_4f2a = true;
        break;
    }
    case 0x202: {
        long position = lparam;
        xy.X = ((short *)&position)[0] - unknown_rect_839630.X;
        xy.Y = ((short *)&position)[1] - unknown_rect_839630.Y;
        if (Planning_Left_Up_00617680(xy)) {
            break;
        }
        if (!unknown_4f2a) {
            break;
        }
        Unknown_00669650(xy, cell, coord, object, arg5, arg6);
        Map.unknown_slot48(coord, cell, object, Unknown_00669960(cell, object, false), false);
        unknown_4f2a = false;
        ReleaseCapture();
        break;
    }
    case 0x204: {
        long position = lparam;
        xy.X = ((short *)&position)[0] - unknown_rect_839630.X;
        xy.Y = ((short *)&position)[1] - unknown_rect_839630.Y;
        Planning_Mouse_Down(xy.X, xy.Y);
        if (unknown_4f2a) {
            break;
        }
        if (!Unknown_00669650(xy, cell, coord, object, arg5, arg6)) {
            break;
        }
        Map.unknown_slot44(xy);
        SetCapture(MainWindow);
        unknown_4f2a = true;
        break;
    }
    case 0x205: {
        long position = lparam;
        Point2D point(((short *)&position)[0] - unknown_rect_839630.X, ((short *)&position)[1] - unknown_rect_839630.Y);
        Planning_Mouse_Up(point.X, point.Y);
        if (!unknown_4f2a) {
            break;
        }
        Map.unknown_slot49(xy);
        DisplayClass::unknown_slot35();
        unknown_4f2a = false;
        ReleaseCapture();
        break;
    }
    case 0x215:
        if (lparam != (long)MainWindow && unknown_4f2a == true) {
            unknown_slot35();
        }
        break;
    }
}
