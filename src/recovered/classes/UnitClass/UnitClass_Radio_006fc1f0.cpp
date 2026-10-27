// Complete Unit radio handler, 0x006FC1F0: 1858 body + 14 padding.
// Includes the original switch tables in the independent bound; not accepted.
// Radio sender downcasts express observed Techno/Foot offsets, not proved types.
// Private Scope12 Cargo query; EAX int/const/source-owner spellings remain hypotheses.
// Uses the bounded Scope12 declaration-only headers; no callee implementation or wrapper.
#include "shared/unit.hpp"
#include "shared/unit_type.hpp"
#include "shared/house.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
extern CoordStruct Unit_Radio_Zero_Coord_00AD04C0;
// @ref ?Unit_Radio_Zero_Coord_00AD04C0@@3UCoordStruct@@A=00ad04c0

static inline double Unit_Radio_Used_Size(UnknownCargo const &cargo) { return (double)cargo.Unknown_00468A20(); }
int UnitClass::unknown_slot95(RadioClass *radio, int message, long &param)
{
    TechnoClass *sender = (TechnoClass *)radio;
    switch (message) {
    case 36:
        if (unknown_slot111()) return 0;
        {
            CellClass &tile = Map[unknown_slot19(0)];
            if ((tile.unknown_140 & 0x100) && !unknown_slot46(0)) return 10;
        }
        if (unknown_slot91() == 16) return 10;
        if (unknown_370) return 10;
        return unknown_574 == -1 ? 1 : 10;
    case 7:
        FootClass::unknown_slot95(radio, message, param);
        unknown_slot260(0, 1);
        unknown_slot220(0);
        unknown_slot116(0, false);
        unknown_4c8c90();
        if (!unknown_370 || !Contact(0)) {
            unknown_slot150(2, sender);
            unknown_slot149(0x18);
        }
        return 1;
    case 15:
        if (Type->Passengers != 0 && radio && House->Is_Ally(sender)) {
            if (unknown_slot111()) return 0;
            if (!sender->unknown_234 &&
                (!radio->unknown_14_bit2 || !((FootClass *)radio)->unknown_580)) {
                if (sender->unknown_230 &&
                    *(int const *)((char const *)sender->unknown_230 + 0x24) != 0) return 0;
                int capacity = Type->Passengers;

                if (!(Unit_Radio_Used_Size(Cargo) + sender->unknown_slot32()->Size <= capacity))
                    goto no_transport_room;
                if (sender->unknown_slot32()->Size > Type->SizeLimit)
                    goto no_transport_room;
                return 1;
            }
        }
        return 0;
    case 22:
        FootClass::unknown_slot95(radio, message, param);
        if (!unknown_599 && unknown_2e0.Current().Raw != 0x4000) {
            Locomotor.Checked()->Do_Turn(UnknownFacingDir(0x4000));
            return 1;
        }
        if (!Locomotor.Checked()->Is_Moving()) {
            TechnoClass *contact = Contact(0);
            if (unknown_370 && contact && contact->Kind_Of() == 6 && unknown_slot91() == 7)
                unknown_slot150(21, contact);
        }
        return 1;
    case 21:
        {
            int capacity = Type->Passengers;
            if (Cargo.Unknown_00468A20() == capacity)
                unknown_2a8.unknown_496bc0(Type->DeployTime);
        }
        return 5;
    case 14:
        if ((Locomotor.Checked()->Is_Moving() || unknown_494) && Mission == 2) return 10;
        if (Contact(0) != radio) {
            int capacity = Type->Passengers;

            if (Unit_Radio_Used_Size(Cargo) + sender->unknown_slot32()->Size <= capacity &&
                !(sender->unknown_slot32()->Size > Type->SizeLimit)) {
                if (!In_Radio_Contact()) unknown_slot150(2, sender);
            } else goto no_transport_room;
        }
        if (!unknown_494) {
            Cell cell = unknown_slot104();
            CellClass &tile = Map[cell];
            int own_zone = Map.Zone(unknown_454, sender->unknown_slot32()->MovementZone, false);
            int sender_zone = -1;
            if (radio && radio->unknown_14_bit2)
                sender_zone = Map.Zone(((FootClass *)radio)->unknown_454,
                                       sender->unknown_slot32()->MovementZone, false);
            if (own_zone != sender_zone) {
                unknown_slot260(radio, 1);
                return 14;
            }
            if (!unknown_494 && tile.unknown_ec == 2) {
                unknown_slot260(radio, 1);
                return 14;
            }
        }
        {
            if (Type->Passengers > 0) {
                int capacity = Type->Passengers;

                if (Unit_Radio_Used_Size(Cargo) + sender->unknown_slot32()->Size <= capacity &&
                    !(sender->unknown_slot32()->Size > Type->SizeLimit)) {
                    FootClass::unknown_slot95(radio, message, param);
                    if (!Locomotor.Checked()->Is_Moving() && !unknown_599 && !unknown_370 &&
                        unknown_slot150(0x13, sender) == 1) {
                        param = (long)this;
                        // Existing long&/int* ABI spellings both occupy one Win32 DWORD.
                        if (unknown_slot151(0x12, (int *)&param, sender) != 1)
                            unknown_slot150(3, sender);
                    }
                    return 1;
                }
            }
        }
        break;
    case 23:
        if ((Type->Harvester || Type->Weeder) && unknown_5b9) {
            unknown_5b9 = false;
            unknown_slot87(Unit_Radio_Zero_Coord_00AD04C0, true, false);
            unknown_slot116(10, false);
            if (unknown_slot122()) unknown_slot117();
        }
        break;
    case 3:
        if (unknown_slot91() == 12) unknown_slot116(5, false);
        FootClass::unknown_slot95(radio, message, param);
        return 1;
    }
    return FootClass::unknown_slot95(radio, message, param);
no_transport_room:
    return 10;
}
