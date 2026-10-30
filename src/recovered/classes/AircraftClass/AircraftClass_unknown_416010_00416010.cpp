// AircraftClass normal move mission 0x00416010 (slot 133 0x00415FF0 tail; Status 0-4: validate LZ, take off,
// fly to LZ, idle, land).
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/id_source.hpp"

// Whether two coordinates lie within one cell of each other on the ground plane.
static inline bool Within_One_Cell(CoordStruct here, CoordStruct target)
{
    UnknownVector3 delta = UnknownVector3(here.X - target.X, here.Y - target.Y, 0);
    return delta.Length() < 256;
}

// The cell under the coordinate a target offers this techno (AbstractClass slot 19).
static inline Cell Destination_Cell(AbstractClass *target, TechnoClass *techno)
{
    return Coord_Cell(target->unknown_slot19(techno));
}

// Do_MISSION_MOVE for aircraft that are not carryalls (0x00415FF0 dispatches here).
int AircraftClass::unknown_416010()
{
    switch (unknown_a8) {
    case 0:
        if (!unknown_494) {
            unknown_slot261(false, true);
        } else {
            unknown_slot260(Select_Landing_Destination_004185b0(unknown_494), 1);
            unknown_a8 = 1;
        }
        break;
    case 1: {
        if (!unknown_494) {
            unknown_slot261(false, true);
            return 1;
        }
        CoordStruct destination = unknown_494->unknown_slot19(this);
        Locomotor.Checked()->Move_To(destination);
        unknown_a8 = 2;
        return 1;
    }
    case 2:
        if (unknown_418 != -1) {
            bool proceed = false;
            if (unknown_494) {
                proceed = Within_One_Cell(Coord, unknown_494->Center_Coord());
            } else {
                proceed = true;
            }
            if (proceed) {
                unknown_4cb110(unknown_player_a35db4->WaypointPaths[unknown_418]->Next_Waypoint(
                    unknown_player_a35db4->WaypointPaths[unknown_418]->Get_Waypoint(unknown_576)));
            }
        }
        if (Locomotor.Checked()->Is_Moving()) {
            if (!unknown_494 || Destination_Cell(unknown_494, this) != unknown_slot104()) {
                if (unknown_494 && !Is_Landing_Cell_Available_00419250(Destination_Cell(unknown_494, this), true)) {
                    unknown_a8 = 0;
                } else {
                    unknown_a8 = 4;
                }
            } else {
                unknown_a8 = 3;
            }
        } else {
            unknown_a8 = 3;
        }
        return 1;
    case 3:
        if (!Locomotor.Checked()->Is_Moving()) {
            unknown_slot261(false, true);
        }
        return 1;
    case 4:
        if (Locomotor.Checked()->Is_Moving()) {
            if (!unknown_494 || Destination_Cell(unknown_494, this) != unknown_slot104()) {
                if (unknown_494 && !Is_Landing_Cell_Available_00419250(Destination_Cell(unknown_494, this), true)) {
                    unknown_a8 = 0;
                }
            } else {
                unknown_a8 = 3;
            }
        } else {
            unknown_a8 = 3;
        }
        return 1;
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
