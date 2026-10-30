// bool FootClass::unknown_4cb110(WaypointClass *waypoint) (0x004CB110)
// Heads for a waypoint of the current path (TibSun Execute_Waypoint_Path
// shape; slots 93 and 194). The player's house fetches the waypoint's path
// (+0x418) and index (+0x576); +0x388 is set while +0x37F holds. A techno in
// the waypoint's cell is clicked (slots 28, 78) when it is an allied building
// that can repair (the unit below full strength, not infantry) or reload it
// (ammo short of the type's) and the action is not 7 or 8, or an enemy whose
// action is not 8, 7, 1 or 2; otherwise the offset cell (+0x41C) moves to a
// nearby cell (0x005502E0) when one is found. The cell plus its offset is
// clicked (slot 77) when its action, the entry test (slot 101) and the
// movement zones agree and the walk (0x0042AA30) is within the offset's
// larger axis plus 3 (at most 5); otherwise the waypoint's cell is, and the
// offset is cleared. Sound is muted meanwhile. Failure clears the path.
// Returns whether the click succeeded.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_type.hpp"
#include "shared/building_type.hpp"
#include "shared/house.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/path_estimator.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_k=00865f00

bool FootClass::unknown_4cb110(WaypointClass *waypoint)
{
    bool succeeded = false;

    if (unknown_37f) {
        unknown_388 = true;
    }

    if (waypoint != 0) {
        unknown_player_a35db4->unknown_func_4ed2b0(waypoint, &unknown_418, &unknown_576);

        CoordStruct coord = waypoint->Coord;
        ObjectClass *occupier = ((UnknownCellClass *)&Map[coord])->unknown_e4;
        TechnoClass *techno = occupier->As_Techno();

        unknown_420 = Coord_Cell(coord);

        bool sound = unknown_sound_enabled_7d88d6;
        unknown_sound_enabled_7d88d6 = false;

        Cell cell = Coord_Cell(coord);
        int action;
        bool direct = true;
        bool click = false;

        if (techno != 0) {
            action = unknown_slot28(occupier, true);

            if (unknown_player_a35db4->Is_Ally(techno->House)) {
                if (techno->Kind_Of() == 6) {
                    BuildingClass *building = (BuildingClass *)techno;
                    bool repair = building->Type->UnitRepair && Strength < unknown_slot32()->MaxStrength && Kind_Of() != 15;
                    bool reload = building->Type->UnitReload && unknown_254 < unknown_slot32()->Ammo && unknown_254 != -1;
                    bool allied = building->House->Is_Ally(unknown_player_a35db4);
                    if ((repair || reload) && allied && action != 7 && action != 8) {
                        click = true;
                    }
                }
            } else if (action != 8 && action != 7 && action != 1 && action != 2) {
                click = true;
            }

            if (!click) {
                Cell nearby = Map.Unknown_005502E0(cell, unknown_slot32()->SpeedType, Map.Zone(cell, unknown_slot32()->MovementZone, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1), unknown_slot32()->MovementZone, false, Point2D(1, 1), 0, 1, 0, 1, Cell(0, 0), 0);
                if (nearby != unknown_geometry_k) {
                    unknown_41c = nearby - cell;
                    direct = false;
                }
            }
        }

        if (click) {
            action = unknown_slot28(occupier, true);
            succeeded = unknown_slot78(action, (int)occupier, true);
            unknown_41c = Cell(0, 0);
        } else {
            action = unknown_slot27(&cell, false, true);
            Cell offset = unknown_41c;
            Cell adjusted = cell + offset;
            UnknownCellClass *adjusted_cell = (UnknownCellClass *)&Map[adjusted];
            UnknownCellClass *cell_ptr = (UnknownCellClass *)&Map[cell];
            int adjusted_action = unknown_slot27(&adjusted, false, true);
            int zone = Map.Zone(cell, unknown_slot32()->MovementZone, cell_ptr->Flags >> 8 & 1);
            int adjusted_zone = Map.Zone(adjusted, unknown_slot32()->MovementZone, adjusted_cell->Flags >> 8 & 1);
            int dest_zone = Map.Zone(Coord_Cell(unknown_slot19(0)), unknown_slot32()->MovementZone, unknown_slot46(0));
            int entry = unknown_slot101((CellClass *)adjusted_cell, -1, adjusted_cell->unknown_11b + (adjusted_cell->Flags >> 8 & 1) * 4, 0, 1);

            int limit = abs(offset.X) > abs(offset.Y) ? abs(offset.X) : abs(offset.Y);
            limit = limit + 3 > 5 ? 5 : limit + 3;

            if ((action == adjusted_action || !direct) && entry == 0 && zone == adjusted_zone && dest_zone == zone
                && (!direct || unknown_path_estimator_8315c8.Unknown_0042AA30(adjusted, cell, this, adjusted_cell->Flags >> 8 & 1, cell_ptr->Flags >> 8 & 1, -1) <= limit)) {
                Cell none(-1, -1);
                succeeded = unknown_slot77(action, (int)&adjusted, (int)&none, true);
                unknown_420 = adjusted;
            } else {
                Cell none(-1, -1);
                succeeded = unknown_slot77(action, (int)&cell, (int)&none, true);
                unknown_41c = Cell(0, 0);
            }
        }

        if (sound) {
            unknown_sound_enabled_7d88d6 = true;
        }
    }

    if (!succeeded) {
        unknown_418 = -1;
        unknown_576 = 0;
        unknown_41c = Cell(0, 0);
        unknown_420 = Cell(0, 0);
    }

    unknown_388 = false;
    return succeeded;
}
