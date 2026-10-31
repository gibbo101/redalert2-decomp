// void FootClass::unknown_slot93(int why) (0x004C7220, slot 93)
// Per-cell processing (TibSun Per_Cell_Process shape). When a move ends in a
// cell (why 2): clears +0x59C and +0x59A; a type with SensorsSight moves its
// sensor cells; the adjacency counts (+0x122) of the cells around the last
// cell (+0x454) move to the current cell, with 0x006D95D0/0x006D95A0 when
// the 0x0054E370 block changes; a cloaked object (+0x1B8 2) shimmers next to
// an enemy with Sensors or ability 12; an attack-type mission (21, 11, 1, 15)
// whose foot target is in range stops; while not cloaked the cell's tag and
// the horizontal, vertical and zone-entry map tags spring (events 1, 0x35
// and 0x36 for agents, 0x19, 0x1A, 0x18); a laser fence below state 8 hurts
// with the C4 warhead; a bridge object off a bridge cell falls (slot 57);
// an object off the visible map that should be deleted is (slots 282, 60);
// a selected object of a non-player house in shroud is unselected. Then a
// waypoint path's next waypoint (or the one being dragged on the map) is
// re-headed for when its offset cell changed, or the path is cleared.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_type.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/tag.hpp"
#include "shared/scenario_tags.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_k=00865f00
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

void FootClass::unknown_slot93(int why)
{
    if (why == 2) {
        unknown_59c = false;
        unknown_59a = false;

        if (unknown_slot32()->SensorsSight != 0) {
            unknown_slot286(unknown_454);
            unknown_slot285(unknown_geometry_k);
        }

        if (unknown_454 != Cell(0, 0)) {
            if (Map.Unknown_0054E370(unknown_454) != Map.Unknown_0054E370(unknown_slot104())) {
                unknown_6d95d0((UnknownCellClass *)&Map[unknown_454]);
                unknown_6d95a0((UnknownCellClass *)unknown_slot105());
            }
            int face;
            for (face = 0; face < 8; face++) {
                Cell c = Adjacent_Cell(unknown_454, face);
                UnknownCellClass *cptr = (UnknownCellClass *)&Map[c];
                cptr->unknown_122--;
            }
            unknown_454 = unknown_slot104();
            for (face = 0; face < 8; face++) {
                Cell c = Adjacent_Cell(unknown_454, face);
                UnknownCellClass *cptr = (UnknownCellClass *)&Map[c];
                cptr->unknown_122++;
            }
        }

        if (unknown_1b8 == 2) {
            for (int face = 0; face < 8; face++) {
                Cell cell = AdjacentCell[face & 7] + unknown_slot104();

                if (Map.Unknown_0055A660(cell, true)) {
                    TechnoClass *techno = ((UnknownCellClass *)&Map[cell])->Unknown_00471660(Point2D(0, 0), 0, 0);

                    if (techno && !techno->House->Is_Ally(this) && (techno->unknown_slot32()->Sensors || techno->unknown_6d7910(12))) {
                        unknown_slot61();
                        break;
                    }
                }
            }
        }

        int primary = unknown_slot174(unknown_228);
        bool inrange = false;
        if (unknown_228 != 0 && unknown_228->unknown_14_bit2) {
            inrange = unknown_slot84(((FootClass *)unknown_228)->unknown_slot287(), primary);
        }

        if ((unknown_slot91() == 21 || unknown_slot91() == 11 || unknown_slot91() == 1 || unknown_slot91() == 15) && inrange && unknown_478.Count() == 0) {
            unknown_slot260(0, 1);
            Path[0] = -1;
        }

        Cell cell = unknown_slot104();
        UnknownCellClass *cellptr = (UnknownCellClass *)&Map[cell];

        if (unknown_1b8 != 2) {
            TagClass *tag = cellptr->unknown_3c;
            int x = cell.X;
            int y = cell.Y;
            if ((!(cellptr->Flags & 0x500) || unknown_79) && tag != 0) {
                tag->Spring(1, this, unknown_slot104());
                if (Kind_Of() == 15 && ((InfantryClass *)this)->Type->Agent) {
                    tag->Spring(0x35, this, unknown_slot104());
                    tag->Spring(0x36, this, unknown_slot104());
                }
            }

            if (cellptr->Flags & 0x100000) {
                for (int index = 0; index < Map.unknown_128; index++) {
                    cellptr = (UnknownCellClass *)&Map[Cell(index + Map.unknown_120, y)];
                    tag = cellptr->unknown_3c;
                    if (tag != 0) {
                        if (tag->unknown_func_6b3da0()) {
                            tag->Spring(0x19, this, unknown_slot104());
                        }
                    }
                }
            }

            if (cellptr->Flags & 0x200000) {
                for (int index = 0; index < Map.unknown_12c; index++) {
                    tag = ((UnknownCellClass *)&Map[Cell(x, index + Map.unknown_124)])->unknown_3c;
                    if (tag != 0) {
                        if (tag->unknown_func_6b3d90()) {
                            tag->Spring(0x1A, this, unknown_slot104());
                        }
                    }
                }
            }

            for (unknown_tag_position_a35e24 = 0; unknown_tag_position_a35e24 < unknown_tags_866238.Count(); unknown_tag_position_a35e24++) {
                tag = unknown_tags_866238[unknown_tag_position_a35e24];
                if (tag != 0) {
                    if (tag->unknown_func_6b3db0()) {
                        if (Map.Unknown_0054F7C0(tag->Get_Cell(), Coord_Cell(unknown_slot19(0)), unknown_slot32()->MovementZone, ((UnknownCellClass *)&Map[tag->Get_Cell()])->Flags >> 8 & 1, unknown_slot46(0), false)) {
                            tag->Spring(0x18, this, Coord_Cell(unknown_slot19(0)));
                        }
                    }
                }
            }
        }

        BuildingClass *building = cellptr->Unknown_004717B0();
        if (building != 0) {
            if (building->Type->LaserFence && building->unknown_4ec < 8) {
                int rtti = Kind_Of();
                if (rtti > 0 && (rtti <= 2 || rtti == 15) && Strength > 0) {
                    unknown_slot86(&Strength, 0, Rules->unknown_c74, (TechnoClass *)building, true, true);
                }
            }
        }

        if (unknown_79 && !(((UnknownCellClass *)&Map[CoordStruct(Coord)])->Flags & 0x100)) {
            unknown_slot57();
        }

        if (!unknown_7d) return;

        if (!Map.Unknown_0055A660(unknown_slot104(), true) && unknown_slot282()) {
            unknown_slot60();
            return;
        }

        if (unknown_77 && !House->Unknown_004F52B0() && Map.Unknown_00568140(CoordStruct(Coord))) {
            unknown_slot81();
        }
    }

    if (unknown_418 != -1) {
        WaypointPathClass *path = unknown_player_a35db4->WaypointPaths[unknown_418];
        WaypointClass *next = path->Get_Waypoint(unknown_576);
        if (next != 0) {
            Cell wp_cell = Coord_Cell(next->Coord);
            if (Map.unknown_11b8 == &next->Coord) {
                wp_cell = Coord_Cell(Map.unknown_11bc);
            }
            if (unknown_41c + wp_cell != unknown_420) {
                unknown_4cb110(next);
            }
        } else {
            unknown_418 = -1;
            unknown_576 = 0;
            unknown_41c = Cell(0, 0);
            unknown_420 = Cell(0, 0);
        }
    }

    TechnoClass::unknown_slot93(why);
}
