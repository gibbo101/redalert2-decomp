// void MapClass::Unknown_00549C20(int arg1, int arg2, CoordStruct const &coord, int sight, HouseClass *house, bool arg6, bool arg7, bool arg8, bool arg9) (0x00549C20)
// Forwards to 0x00549C50 with true for its last argument; the first two
// arguments are not read (no callers or pointers in the executable).
#include "shared/map.hpp"

void MapClass::Unknown_00549C20(int arg1, int arg2, CoordStruct const &coord, int sight, HouseClass *house, bool arg6, bool arg7, bool arg8, bool arg9)
{
    Unknown_00549C50(coord, sight, house, arg6, arg7, arg8, arg9, true);
}
