// Aircraft carryall branch of movement slot133, original00416670, complete1444+12.
// Private typed diagnostic candidate, not accepted; one own nonvirtual declaration proposal.
// All446 code instructions and four original switch edges: R354 original-only proof.
// Existing UnknownCellClass view and Foot subtype interpretation remain hypotheses.
// No new Cell/Rules/Bullet fields or foreign interface is proposed or applied.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/id_source.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Select_Landing_Destination_004185b0@AircraftClass@@QAEPAVAbstractClass@@PAV2@@Z=004185b0
// @ref ?unknown_416420@AircraftClass@@QAEXXZ=00416420
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Unknown_00473E30@UnknownCellClass@@QAEPAVFootClass@@_N@Z=00473e30
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref _unknown_aircraft_move_log_7ce968=007ce968
extern "C" char const unknown_aircraft_move_log_7ce968[];
// @ref _unknown_aircraft_move_log_7ce92c=007ce92c
extern "C" char const unknown_aircraft_move_log_7ce92c[];
// @ref _unknown_aircraft_move_log_7ce8f0=007ce8f0
extern "C" char const unknown_aircraft_move_log_7ce8f0[];
// @ref _unknown_aircraft_move_log_7ce8a8=007ce8a8
extern "C" char const unknown_aircraft_move_log_7ce8a8[];
// @ref _unknown_aircraft_move_log_7ce854=007ce854
extern "C" char const unknown_aircraft_move_log_7ce854[];
// @ref _unknown_aircraft_move_log_7ce818=007ce818
extern "C" char const unknown_aircraft_move_log_7ce818[];
// @ref _unknown_aircraft_move_log_7ce7e0=007ce7e0
extern "C" char const unknown_aircraft_move_log_7ce7e0[];
// @ref _unknown_aircraft_move_log_7ce7a8=007ce7a8
extern "C" char const unknown_aircraft_move_log_7ce7a8[];
// @ref _unknown_aircraft_move_log_7ce770=007ce770
extern "C" char const unknown_aircraft_move_log_7ce770[];
// @ref _unknown_aircraft_move_log_7ce738=007ce738
extern "C" char const unknown_aircraft_move_log_7ce738[];
// @ref _unknown_aircraft_move_log_7ce714=007ce714
extern "C" char const unknown_aircraft_move_log_7ce714[];
// @ref _unknown_aircraft_move_log_7ce6e0=007ce6e0
extern "C" char const unknown_aircraft_move_log_7ce6e0[];
// @ref _unknown_aircraft_move_log_7ce6ac=007ce6ac
extern "C" char const unknown_aircraft_move_log_7ce6ac[];
// @ref _unknown_aircraft_move_log_7ce664=007ce664
extern "C" char const unknown_aircraft_move_log_7ce664[];

int AircraftClass::Move_Carryall_00416670()
{
    CoordStruct bridge_position;
    CoordStruct occupant_position;
    switch (unknown_a8) {
    case 0: {
        Debug_Printf(unknown_aircraft_move_log_7ce968);
        if (!unknown_494) {
            Debug_Printf(unknown_aircraft_move_log_7ce92c);
            unknown_slot261(false, true);
            break;
        }
        TechnoClass *target = unknown_494->As_Techno();
        if (target && !Cargo.Object && House->Is_Ally(target)) {
            // Models the original byte temporary; source type/spelling remain nonunique.
            bool const &target_is_techno = target->AbstractFlags.IsTechno;
            if (target_is_techno && !target->Owning_House()->Is_Ally(this)) goto select_destination;
            if (target->Kind_Of() == 1) {
                Debug_Printf(unknown_aircraft_move_log_7ce8f0);
                if (Contact(0) != target) unknown_slot149(3);
                if (unknown_slot150(2, target) == 1) {
                    Debug_Printf(unknown_aircraft_move_log_7ce8a8);
                    if (unknown_slot149(36) != 1) {
                        Debug_Printf(unknown_aircraft_move_log_7ce854);
                        unknown_slot149(3);
                        unknown_slot261(false, true);
                        break;
                    }
                    unknown_slot149(7);
                } else {
                    unknown_slot260(0, 1);
                    unknown_slot261(false, true);
                    break;
                }
            }
        }
select_destination:
        unknown_slot260(Select_Landing_Destination_004185b0(unknown_494), 1);
        if (Team) Team->unknown_func_6b79e0(unknown_494);
        unknown_a8 = 1;
        Debug_Printf(unknown_aircraft_move_log_7ce818);
        break;
    }
    case 1: {
        if (!unknown_494) {
            unknown_slot261(false, true);
            return 1;
        }
        CoordStruct destination = unknown_494->Center_Coord();
        Locomotor.Checked()->Move_To(destination);
        unknown_a8 = 2;
        return 1;
    }
    case 2:
        if (unknown_494 && unknown_494->Kind_Of() != 11 && Contact(0) != unknown_494) {
            Debug_Printf(unknown_aircraft_move_log_7ce7e0);
            unknown_a8 = 0;
            return 1;
        }
        if (unknown_494 && unknown_494->Kind_Of() == 11 && !unknown_slot309(unknown_494)) {
            unknown_a8 = 0;
            return 1;
        }
        if (Locomotor.Checked()->Get_Status() == 1) {
            Debug_Printf(unknown_aircraft_move_log_7ce7a8);
            if (unknown_494 && unknown_494->Kind_Of() == 1) {
                CoordStruct current_position = Coord;
                Cell current_cell = Coord_Cell(current_position);
                CoordStruct target_position = static_cast<ObjectClass *>(unknown_494)->Coord;
                Cell target_cell = Coord_Cell(target_position);
                if (target_cell != current_cell) {
                    unknown_a8 = 0;
                    Debug_Printf(unknown_aircraft_move_log_7ce770);
                    return 1;
                }
            }
            unknown_5bc = false;
        }
        if (!Locomotor.Checked()->Is_Moving()) {
            Debug_Printf(unknown_aircraft_move_log_7ce738);
            unknown_a8 = 3;
        }
        return 1;
    case 3: {
        Debug_Printf(unknown_aircraft_move_log_7ce714);
        if (Cargo.Object && unknown_3f8) {
            unknown_5bc = true;
            return 1;
        }
        if (Cargo.Object) {
            unknown_slot71(0);
            unknown_416420();
            unknown_slot71(1);
            unknown_a8 = 0;
            return 1;
        }
        Debug_Printf(unknown_aircraft_move_log_7ce6e0);
        unknown_slot71(0);
        bridge_position = Coord;
        occupant_position = Coord;
        FootClass *passenger = reinterpret_cast<UnknownCellClass *>(&Map[occupant_position])->Unknown_00473E30(
            (reinterpret_cast<UnknownCellClass *>(&Map[bridge_position])->Flags >> 8) & 1);
        if (passenger && passenger == Contact(0)) {
            Debug_Printf(unknown_aircraft_move_log_7ce6ac);
            if (unknown_slot149(19) == 1) {
                Debug_Printf(unknown_aircraft_move_log_7ce664);
                passenger->unknown_slot52();
                passenger->unknown_79 = false;
                passenger->unknown_37c = true;
                Cargo.Unknown_00468960(passenger);
                goto finalize_pickup;
            }
        }
        unknown_a8 = 0;
finalize_pickup:
        unknown_slot149(3);
        unknown_slot71(1);
        unknown_5bc = true;
        unknown_slot261(false, true);
        return 1;
    }
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
