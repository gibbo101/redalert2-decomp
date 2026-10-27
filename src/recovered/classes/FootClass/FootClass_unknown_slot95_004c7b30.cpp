// int FootClass::unknown_slot95(RadioClass *from, int message, long &param) (0x004C7B30)
// The radio message handler (Westwood's Receive_Message; param is the
// message's long argument):
//   17: in mission 7 (now or queued) the techno reply, answered 1;
//   18: a contact standing in this unit's cell answers 20; otherwise a
//       guarding (5) unit with nothing queued queues mission 2, a queued
//       mission 7 is commenced, the unit heads for the contact and restarts
//       the mission timer (answer 1);
//   19: stores the destination (+0x494) in *param; a unit still moving
//       toward it answers 10, else 1;
//   23: drops a destination that is the radio contact, leaves missions 0
//       and 7 for 5 and, without +0x599 and destination, scatters (slot 87);
//   28: 10 while it has a destination;
//   35: 1 when the sender is the building in this unit's cell, else 10;
// everything else goes to TechnoClass.
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
#include "shared/techno_map.hpp"
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?unknown_slot95@TechnoClass@@UAEHPAVRadioClass@@HAAJ@Z=006c2590

int FootClass::unknown_slot95(RadioClass *from, int message, long &param)
{
    switch (message) {
    case 35:
        return Map_Cell(Center_Coord())->Unknown_004717B0() == (BuildingClass *)from ? 1 : 10;
    case 28:
        if (unknown_494 != 0) {
            return 10;
        }
        break;
    case 23:
        if (In_Radio_Contact() && unknown_494 == Contact(0)) {
            unknown_slot260(0, 1);
        }
        if (unknown_slot91() == 0) {
            unknown_slot116(5, false);
            if (unknown_slot122()) {
                unknown_slot117();
            }
        }
        if (unknown_slot91() == 7) {
            unknown_slot116(5, false);
        }
        if (!unknown_599 && unknown_494 == 0) {
            unknown_slot87(unknown_geometry_l, 1 != 0, 1 != 0);
        }
        break;
    case 19:
        param = (long)unknown_494;
        if (unknown_494 != 0 && Locomotor.Checked()->Is_Moving()) {
            return 10;
        }
        return 1;
    case 18:
        if (param != 0) {
            Cell cell = Coord_Cell(((AbstractClass *)param)->Center_Coord());
            if (unknown_slot104() == cell) {
                return 20;
            }
        }
        if (unknown_slot91() == 5 && MissionQueue == -1) {
            unknown_slot116(2, false);
        }
        if (MissionQueue == 7 && unknown_slot122()) {
            unknown_slot117();
        }
        unknown_slot260((AbstractClass *)param, 1);
        Timer = 0;
        return 1;
    case 17:
        if (unknown_slot91() == 7 || MissionQueue == 7) {
            TechnoClass::unknown_slot95(from, message, param);
            return 1;
        }
        break;
    }
    return TechnoClass::unknown_slot95(from, message, param);
}
