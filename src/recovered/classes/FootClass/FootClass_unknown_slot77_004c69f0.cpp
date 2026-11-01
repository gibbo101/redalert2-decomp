// bool FootClass::unknown_slot77(int action, int arg2, int arg3, bool arg4) (0x004C69F0, slot 77)
// Carries out a click on a cell (arg2 and arg3 are Cell pointers; the
// action argument is recomputed through slot 27): refuses when the map
// rejects the cell unless the action is 2 (move), then queues the order
// through slot 200 by action. A move (1) first plays the move-flash
// animation (Rules +0xA74) when sound is on; in a multiplayer mode it is
// created with a temporary ID and moved from Anims to the second list.
// TibSun Active_Click_With(Cell const &) shape: cases break to the shared
// return true, failures return false.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_4cca40@FootClass@@QAE?AVCell@@ABV2@_N@Z=004cca40
// @ref ?Unknown_00710160@@YIPAUUnknownCellObject710160@@ABVCell@@@Z=00710160
// @ref ?Unknown_0047A130@UnknownCellClass@@QAEPAUUnknownTube47A130@@XZ=0047a130
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref _unknown_geometry_k=00865f00
// @ref _unknown_geometry_j=00865f60

bool FootClass::unknown_slot77(int action, int arg2, int arg3, bool arg4)
{
    Cell const &cell = *(Cell const *)arg2;
    action = unknown_slot27(&cell, false, arg4);

    if (!Map.Unknown_0055A660(cell, true) && action != 2) {
        return false;
    }

    switch (action) {
    case 51:
        if (unknown_slot39()) {
            Cell moveto = unknown_4cca40(cell, false);
            unknown_slot200(0x19, 0, (int)&Map[moveto], 0);
            break;
        }
        return false;

    case 26:
        if ((unknown_slot38() || unknown_slot193()) && unknown_slot39()) {
            unknown_slot200(0xB, (AbstractClass *)&Map[cell], 0, 0);
            break;
        }
        return false;

    case 6:
        unknown_slot200(0xA, 0, (int)&Map[cell], 0);
        break;

    case 1:
    case 62:
        if (unknown_sound_enabled_7d88d6) {
            CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
            coord.Z = Map.Unknown_0055A280(coord);
            if (((UnknownCellClass *)&Map[coord])->Flags & 0x100) {
                coord.Z += unknown_geometry_j;
            }
            long scenid = unknown_id_source_a3d290->UniqueID;
            if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
                unknown_id_source_a3d290->UniqueID = -3;
                Rules->unknown_a74->YSortAdjust = -5000;
            }
            AnimClass *moveflash = new AnimClass(Rules->unknown_a74, coord, 0, 1, 0x600, 0);
            if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
                unknown_id_source_a3d290->UniqueID = scenid;
                Anims.Delete(moveflash);
                unknown_anims_a35e60.Add(moveflash);
            }
        }
        // Fall into next case.

    case 2: {
        Cell moveto = unknown_4cca40(cell, false);
        if (moveto != unknown_geometry_k) {
            unknown_slot200(2, 0, (int)&Map[moveto], (int)&Map[*(Cell const *)arg3]);
            break;
        }
    }
        return false;

    case 5:
    case 63: {
        UnknownCellObject710160 *veinhole = Unknown_00710160(cell);
        if (veinhole != 0 && !veinhole->unknown_e8 && veinhole->unknown_6c > 0) {
            unknown_slot200(1, (AbstractClass *)veinhole, 0, 0);
            break;
        } else {
            unknown_slot200(1, (AbstractClass *)&Map[cell], 0, 0);
            break;
        }
    }
        return false;

    case 9:
        if (unknown_slot39()) {
            unknown_slot200(8, 0, (int)&Map[cell], 0);
            break;
        }
        return false;

    case 3:
        if (unknown_slot39()) {
            unknown_slot200(7, 0, (int)&Map[cell], 0);
            break;
        }
        return false;

    case 16:
        unknown_slot200(0x11, 0, (int)&Map[cell], 0);
        break;

    case 35: {
        UnknownTube47A130 *tunnel = ((UnknownCellClass *)&Map[cell])->Unknown_0047A130();
        UnknownTube47A130 *exittunnel = ((UnknownCellClass *)&Map[Cell(tunnel->unknown_28)])->Unknown_0047A130();
        Cell exit = Adjacent_Cell(Cell(tunnel->unknown_28), (exittunnel->unknown_2c - 4) & 7);
        unknown_slot200(2, 0, (int)&Map[exit], 0);
        break;
    }
    }
    return true;
}
