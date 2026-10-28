// int TechnoClass::unknown_slot25(bool arg1, int arg2) (0x006CF3C0, slot 25)
// How the object is drawn (hypothesis: Visual_Character; 0 normal,
// 1 indistinct, 2 darken, 3 shadowy, 4 ripple, 5 hidden): an Invisible type
// is hidden unless +0x372 or the 0x00A40D13 flag; a cloaked object (+0x1B8
// state 2) is shadowy where its cell is revealed to the house (arg2, a
// HouseClass pointer, when arg1 is set; else the player, or mutual allies in
// a multiplayer mode) and hidden otherwise; while cloaking or uncloaking the
// cloak stage scaled to 256 picks 1-5.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref __real@8@40078000000000000000=0079a700

int TechnoClass::unknown_slot25(bool arg1, int arg2)
{
    if (unknown_slot32()->Invisible && unknown_372) {
        return 0;
    }
    if (unknown_slot32()->Invisible && !unknown_372 && !unknown_flag_a40d13) {
        return 5;
    }
    if (unknown_1b8 == 0 || unknown_flag_a40d13) {
        return 0;
    }
    if (Kind_Of() == 6) {
        return 0;
    }
    if (unknown_1b8 == 2) {
        if (arg1) {
            HouseClass *house = (HouseClass *)arg2;
            if (house != 0) {
                Cell cell = Coord_Cell(CoordStruct(Coord));
                if (((UnknownCellClass *)&Map[cell])->unknown_47c2e0(house->ArrayIndex)) {
                    return 3;
                }
            }
        } else {
            if (unknown_b263d8 == 0) {
                return 3;
            }
            if (unknown_372) {
                return 3;
            }
            Cell cell = Coord_Cell(CoordStruct(Coord));
            if (((UnknownCellClass *)&Map[cell])->unknown_47c2e0(unknown_player_a35db4->ArrayIndex)) {
                return 3;
            }
            if (unknown_game_mode_a3d298 != 0 && House != 0 && unknown_player_a35db4 != 0
                && unknown_player_a35db4->Is_Ally(House) && House->Is_Ally(unknown_player_a35db4)) {
                return 3;
            }
        }
        return 5;
    }
    int stage = unknown_1bc.Value;
    if (stage > 0) {
        int level = (int)((double)stage / Rules->unknown_548 * 256.0);
        if (level < 64) {
            return 1;
        }
        if (level < 128) {
            return 2;
        }
        if (level < 192) {
            return 3;
        }
        if (!arg1 && unknown_372) {
            return 3;
        }
        return level >= 255 ? 5 : 4;
    }
    return 0;
}
