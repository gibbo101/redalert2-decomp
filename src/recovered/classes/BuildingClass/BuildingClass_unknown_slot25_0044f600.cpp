// int BuildingClass::unknown_slot25(bool arg1, int arg2) (0x0044F600, slot 25)
// While +0x5BD is set: 1 or 2 up to 10 (2 above 5); above 10, 3 when the
// house arg2 (a HouseClass *) holds the bit 0x0047C2E0 of this cell (with
// arg1), or, without arg1, when +0x372 or slot 191 holds, there is no main
// window, or the player and the owner are mutual allies in a game mode;
// otherwise 5. Without +0x5BD the techno behaviour.
#include "shared/building.hpp"
#include "shared/win32_window.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0
// @ref ?unknown_slot25@TechnoClass@@UAEH_NH@Z=006cf3c0

extern HWND MainWindow;                 // 0x00B263D8

int BuildingClass::unknown_slot25(bool arg1, int arg2)
{
    if (unknown_5bd) {
        if (unknown_5bd > 10) {
            if (arg1) {
                HouseClass *house = (HouseClass *)arg2;
                if (house) {
                    CoordStruct coord = Coord;
                    if (((UnknownCellClass *)&Map[Coord_Cell(coord)])->unknown_47c2e0(house->ArrayIndex)) {
                        return 3;
                    }
                }
            } else {
                if (unknown_372 || unknown_slot191() || !MainWindow
                    || unknown_game_mode_a3d298 && House && unknown_player_a35db4
                    && unknown_player_a35db4->Is_Ally(House) && House->Is_Ally(unknown_player_a35db4)) {
                    return 3;
                }
            }
            return 5;
        }
        return (unknown_5bd > 5) + 1;
    }
    return TechnoClass::unknown_slot25(arg1, arg2);
}
