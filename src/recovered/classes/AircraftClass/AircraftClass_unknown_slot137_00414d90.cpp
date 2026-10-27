// AircraftClass mission slot137, 0x00414D90. Complete1024 bytes includes five-way dispatch table.
// State names remain provisional; original call and read ordering retained.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/id_source.hpp"
// @ref ?Select_Landing_Destination_004185b0@AircraftClass@@QAEPAVAbstractClass@@PAV2@@Z=004185b0
// @ref ?unknown_416420@AircraftClass@@QAEXXZ=00416420
// @ref ?unknown_4198b0@AircraftClass@@QAEPAVAbstractClass@@XZ=004198b0
// @ref _unknown_geometry_k=0083c478
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@4008e100000000000000=0079b608
// @ref __real@8@00000000000000000000=0079b610
int AircraftClass::unknown_slot137()
{
    switch (unknown_a8) {
    case 0:
        if (unknown_slot108() == 0 && unknown_240 == 0.0) {
            if (unknown_494) {
                CoordStruct current = Coord;
                if (current != unknown_494->Center_Coord()) goto choose_destination;
            }
            unknown_a8 = 3;
mission_delay:
    default: {
        int delay = (int)(Control()->unknown_10 * 900.0);
        return unknown_id_source_a3d290->Random()(0, 2) + delay;
    }

        }
choose_destination:
        if (!unknown_494 && Type->IsDropship && unknown_slot108() > 0) {
            TechnoClass *dock = unknown_slot299((DynamicVectorClass<TechnoTypeClass *> const *)&Type->Dock, 0, 0);
            if (dock) unknown_slot260(dock, 1);
            else unknown_slot260(unknown_4198b0(), 1);
        } else if (!unknown_494) {
            unknown_a8 = 2;
        } else if (unknown_slot309(unknown_494)) {
            FootClass *passenger = (FootClass *)Cargo.unknown_468a10();
            if (!passenger || !passenger->Team || passenger->Team->Class->Waypoint_Location() == unknown_geometry_k) {
                unknown_slot260(Select_Landing_Destination_004185b0(&Map[unknown_id_source_a3d290->Get_Waypoint_Location(99)]), 1);
                if (Team) Team->unknown_func_6b79e0(unknown_494);
            } else {
                unknown_slot260(Select_Landing_Destination_004185b0(&Map[passenger->Team->Class->Waypoint_Location()]), 1);
            }
        } else {
            int flight_level = Type->Flight_Level();
            unknown_a8 = unknown_slot108() == flight_level ? 1 : 4;
        }
        goto mission_delay;
    case 1:
        if (!Locomotor.Checked()->Is_Moving()) unknown_a8 = 2;
        if (!unknown_slot309(unknown_494)) unknown_a8 = 0;
        goto mission_delay;
    case 2:
        if (!Locomotor.Checked()->Is_Moving()) unknown_a8 = 3;
        return 1;
    case 3:
        if (!unknown_370) {
            if (Cargo.Object) {
                if (Type->Carryall) {
                    unknown_slot71(0);
                    unknown_416420();
                    unknown_slot71(1);
                } else {
                FootClass *passenger = (FootClass *)Cargo.unknown_4689f0();
                Map.Unknown_0054AF70(unknown_slot104(), this);
                if (unknown_slot62(passenger)) passenger->unknown_37c = false;
                Map.Unknown_0054AB70(unknown_slot104(), this);
                if (!passenger->unknown_37c && passenger->Team) Team->unknown_func_6b8cc0(passenger);
                if (!Cargo.Object) unknown_slot261(false, true);
                }
            } else {
                unknown_slot261(false, true);
            }
        }
        goto mission_delay;
    case 4:
        unknown_a8 = 0;
        return 1;
    }
}
