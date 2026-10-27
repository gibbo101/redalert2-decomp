// void RadarClass::AI(int &input, Point2D const &xy) (0x0062FCC0, slot 10)
// After the display's AI: the normal mouse over either radar button (shifted
// right by the tactical width when the sidebar is on the right), the
// button presses (0x80F2 selects mode 9 outside multiplayer or with a
// ready session in game modes 3/4, else 8; 0x80F3 mode 1), the forced
// transmission mode 4 while 0x00AF8FE8 is positive, then the mode-4 update
// or 0x00716950.
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?AI@DisplayClass@@UAEXAAHABUPoint2D@@@Z=00499a20
// @ref ?Override_Mouse_Shape@MouseClass@@UAE_NH_N@Z=0059f250
// @ref ?Unknown_00633000@RadarClass@@QAEXH_N@Z=00633000
// @ref ?Unknown_00633C40@RadarClass@@QAEXXZ=00633c40
// @ref ?Unknown_00716950@@YAXXZ=00716950
// @ref ?unknown_int_a40d48@@3HA=00a40d48
// @ref ?unknown_rect_ab6468@@3VRect@@A=00ab6468
// @ref ?unknown_rect_ab6338@@3VRect@@A=00ab6338
// @ref ?unknown_int_af8fe8@@3HA=00af8fe8
// @ref ?unknown_session_a3d29c@@3PAVUnknownSessionA3D29C@@A=00a3d29c

void RadarClass::AI(int &input, Point2D const &xy)
{
    DisplayClass::AI(input, xy);
    int offset = unknown_flag_a40b30 ? unknown_int_839638 : 0;
    Rect area = unknown_rect_ab6468;
    area.X += offset;
    if (area.Is_Point_Within(xy)) {
        Map.Override_Mouse_Shape(0, false);
    }
    area = unknown_rect_ab6338;
    area.X += offset;
    if (area.Is_Point_Within(xy)) {
        Map.Override_Mouse_Shape(0, false);
    }
    if (input == 0x80F2) {
        if (unknown_game_mode_a3d298 == 0
            || ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_session_a3d29c != 0
                && unknown_session_a3d29c->unknown_slot2() && unknown_session_a3d29c->unknown_slot1())) {
            unknown_int_a40d48 = 9;
        } else {
            unknown_int_a40d48 = 8;
        }
    } else if (input == 0x80F3) {
        unknown_int_a40d48 = 1;
    }
    if (unknown_int_af8fe8 > 0 && unknown_14ac != 3 && unknown_14ac != 4) {
        unknown_14b0 = unknown_14ac;
        Unknown_00633000(4, false);
        unknown_14b4 = 0;
    }
    if (unknown_14ac == 4) {
        Unknown_00633C40();
    } else {
        Unknown_00716950();
    }
}
