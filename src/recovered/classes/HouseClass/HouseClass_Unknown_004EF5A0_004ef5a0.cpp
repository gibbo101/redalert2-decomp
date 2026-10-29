// void HouseClass::Unknown_004EF5A0() (0x004EF5A0)
// After the MCV deploys (UnitClass 0x006FDFC0): a computer house in a
// multiplayer game runs 0x004EC5E0; a house without base nodes plans its
// base (0x004EF890) with unknown_a40774 cleared.
// @ref ?unknown_func_4ef890@HouseClass@@QAEXXZ=004ef890
#include "shared/house.hpp"
#include "shared/base.hpp"

void HouseClass::Unknown_004EF5A0()
{
    if (!Is_Human_Control() && unknown_game_mode_a3d298 != 0) {
        unknown_func_4ec5e0();
    }
    if (unknown_55f0.Nodes.Count() == 0) {
        int saved = unknown_a40774;
        unknown_a40774 = 0;
        unknown_func_4ef890();
        unknown_a40774 = saved;
    }
}
