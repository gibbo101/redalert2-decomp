// bool TechnoClass::unknown_slot52() (0x006C4480, slot 52)
// Takes an active techno off the map: slot 263 (revealing to the player for
// RevealToAll types), clears its sight (0x0054A550 around +0x1F4), GapGenerator
// slot 236, BombSight types leave the 0x008322E0 list, the owner forgets it
// (0x004ED440); with slot 168 positive the cell (a foot's +0x454, else slot
// 105) takes back -+0x400 for the owner; slot 265 for +0x37B; the audio at
// +0x3D8 stops; then RadioClass slot 52.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_list_8322e0@@3VUnknownList8322E0@@A=008322e0
// @ref ?Unknown_004366D0@UnknownList8322E0@@QAEXPAVTechnoClass@@@Z=004366d0
// @ref ?Unknown_004ED440@HouseClass@@QAEXPAVTechnoClass@@_N@Z=004ed440
// @ref ?unknown_476b20@UnknownCellClass@@QAEXHH@Z=00476b20
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
// @ref ?unknown_slot52@RadioClass@@UAE_NXZ=00636b60

bool TechnoClass::unknown_slot52()
{
    if (!unknown_76 && unknown_slot32() != 0) {
        if (unknown_slot32()->RevealToAll) {
            unknown_slot263(0, 0, true, unknown_player_a35db4);
        } else {
            unknown_slot263(0, 0, false, 0);
        }
        Map.Unknown_0054A550(CoordStruct(Coord), unknown_1f4 - 3, unknown_1f4 + 3, 0);
        if (unknown_slot32()->GapGenerator) {
            unknown_slot236();
        }
        if (unknown_slot32()->BombSight != 0) {
            unknown_list_8322e0.Unknown_004366D0(this);
        }
        House->Unknown_004ED440(this, false);
        if (unknown_slot168() > 0) {
            UnknownCellClass *cell;
            if (this != 0 && unknown_14_bit2) {
                cell = (UnknownCellClass *)&Map[((FootClass *)this)->unknown_454];
                if (cell != 0) {
                    cell->unknown_476b20(Owner(), -unknown_400);
                    unknown_400 = 0;
                }
            } else {
                cell = (UnknownCellClass *)unknown_slot105();
                if (cell != 0) {
                    cell->unknown_476b20(Owner(), -unknown_400);
                    unknown_400 = 0;
                }
            }
        }
        if (unknown_37b) {
            unknown_slot265();
        }
        unknown_3d8.Unknown_00406070();
        unknown_3ec = 1;
        unknown_3f0 = 0;
    }
    return RadioClass::unknown_slot52();
}
