// void WaveClass::unknown_slot67(int arg1, int arg2) (0x00722530)
// Draws the wave by its type unless both ends are hidden (tunnels).
#include "shared/wave.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_005683C0@MapClass@@QAE_NABUCoordStruct@@@Z=005683c0
// @ref ?unknown_func_7225b0@WaveClass@@QAEXHH@Z=007225b0
// @ref ?unknown_func_722cb0@WaveClass@@QAEXHH@Z=00722cb0

void WaveClass::unknown_slot67(int arg1, int arg2)
{
    if ((unknown_id_source_a3d290->unknown_000 & 0x1000) && Map.Unknown_005683C0(unknown_a0) && Map.Unknown_005683C0(unknown_ac)) {
        return;
    }
    switch (Type) {
    case 0:
        unknown_func_7225b0(arg1, arg2);
        break;
    case 1:
    case 2:
        unknown_func_722cb0(arg1, arg2);
        break;
    }
}
