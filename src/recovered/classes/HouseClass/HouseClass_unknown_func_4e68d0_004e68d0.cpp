// bool HouseClass::unknown_func_4e68d0(int index, Cell const *cell) (0x004E68D0)
// Acts on a super weapon (0x0069D090); a linked super weapon takes over its
// +0x4A cell first and is updated after it.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
// @ref ?unknown_func_69d090@UnknownSuperView@@QAEX_NPBVCell@@@Z=0069d090

bool HouseClass::unknown_func_4e68d0(int index, Cell const *cell)
{
    UnknownSuperView *super = (UnknownSuperView *)Supers[index];
    UnknownSuperView *linked = 0;
    if (super->Type->unknown_e1) {
        linked = (UnknownSuperView *)Supers[super->Type->unknown_e4];
        if (linked != 0) {
            super->unknown_4a = linked->unknown_4a;
        }
    }
    super->unknown_func_69d090(this == unknown_player_a35db4, cell);
    if (super->Type->unknown_e1 && linked != 0) {
        linked->unknown_func_69cfb0(0);
        linked->unknown_func_69cfc0(this == unknown_player_a35db4);
    }
    return true;
}
