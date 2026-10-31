// AircraftClass::unknown_slot145 0x00416C20: Do_MISSION_PATROL (Status 0-4: validate LZ, take off,
// patrol toward the LZ while looking for a dock when out of ammo or a threat, idle, land).
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/team.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"

// Whether two coordinates lie within one cell of each other on the ground plane (2D length).
static inline bool Near_In_Plane(CoordStruct here, CoordStruct target)
{
    CoordStruct delta(here.X - target.X, here.Y - target.Y, 0);
    double y = delta.Y;
    double x = delta.X;
    return (int)unknown_sqrt_4ba410(x * x + y * y) < 256;
}

int AircraftClass::unknown_slot145()
{
    unknown_37f = true;
    switch (unknown_a8) {
    case 0:
        if (!unknown_494) {
            unknown_slot261(false, true);
        } else {
            unknown_slot260(Select_Landing_Destination_004185b0(unknown_494), 1);
            if (Team) {
                Team->unknown_func_6b79e0(unknown_494);
            }
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
    case 2: {
        CoordStruct position;
        if (unknown_254 == 0) {
            TechnoClass *dock = unknown_slot299((DynamicVectorClass<TechnoTypeClass *> const *)&Type->Dock, 0, 0);
            if (dock) {
                unknown_slot119(7, 0, (int)dock);
                unknown_a8 = 0;
                return 1;
            }
        }
        if (unknown_254 != 0) {
            position = Coord;
            AbstractClass *threat = unknown_slot219(2, &position, false);
            if (threat && threat->unknown_14_bit1) {
                unknown_slot119(1, (int)threat, 0);
                unknown_a8 = 0;
                return 1;
            }
        }
        if (unknown_418 != -1) {
            bool proceed = false;
            if (unknown_494) {
                proceed = Near_In_Plane(Coord, unknown_494->Center_Coord());
            } else {
                proceed = true;
            }
            if (proceed) {
                unknown_4cb110(unknown_player_a35db4->WaypointPaths[unknown_418]->Next_Waypoint(
                    unknown_player_a35db4->WaypointPaths[unknown_418]->Get_Waypoint(unknown_576)));
            }
        }
        if (!Locomotor.Checked()->Is_Moving()) {
            unknown_a8 = 3;
        } else {
            if (unknown_494 && !Is_Landing_Cell_Available_00419250(Destination_Cell(unknown_494, this), true)) {
                unknown_a8 = 0;
            } else {
                unknown_a8 = 4;
            }
        }
        return 1;
    }
    case 3:
        unknown_slot261(false, true);
        return 1;
    case 4:
        if (!Locomotor.Checked()->Is_Moving()) {
            unknown_a8 = 3;
        } else {
            if (unknown_494) {
                if (!Is_Landing_Cell_Available_00419250(Destination_Cell(unknown_494, this), true)) {
                    unknown_a8 = 0;
                }
            }
        }
        return 1;
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
