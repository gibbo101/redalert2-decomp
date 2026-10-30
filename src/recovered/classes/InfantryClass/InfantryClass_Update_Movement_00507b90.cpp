// Selects the standing, walking or jumpjet sequence (0x00507B90).
#include "shared/infantry.hpp"
#include "shared/techno_map.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref __real@8@3ffeccccccccccccd000=007a3a30
// @ref ?Release_Held@UnknownPersistPtr@@QAEXXZ=004a4d00
// @ref _CLSID_JumpjetLocomotionClass=007a2000
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054F7C0@MapClass@@QAE_NABVCell@@0H_N11@Z=0054f7c0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
extern "C" GUID const CLSID_JumpjetLocomotionClass;
void InfantryClass::Update_Movement_00507b90()
{
    if (unknown_slot91() == 2 && !Locomotor.Checked()->Is_Moving()) {
        if (unknown_494 == 0) {
            unknown_slot261(false, true);
        } else {
            unknown_slot260(unknown_494, 1);
            unknown_slot306(1.0);
        }
    }
    if (unknown_494 != 0) {
        Cell target_cell = Coord_Cell(unknown_494->unknown_slot19(this));
        if (unknown_5c4 && unknown_slot101(unknown_slot107(), -1, -1, 0, 1) == 7) {
            goto select_sequence;
        }
        if (!Locomotor.Checked()->Is_Moving() && !unknown_370 && unknown_494 != 0 && unknown_32d) {
            Cell current_cell = Coord_Cell(unknown_slot19(0));
            if (!Map.Unknown_0054F7C0(current_cell, target_cell, Type->MovementZone,
            unknown_slot46(0), (unsigned char)((Map[target_cell].unknown_140 >> 8) & 1), unknown_slot189())
            && !Type->Infiltrate && unknown_slot91() != 7) {
                unknown_slot260(0, 1);
            }
        }
    }
select_sequence:
    if (Locomotor.Checked()->Is_Really_Moving_Now()) {
        if (Type->JumpJet) {
            bool is_jumpjet;
            {
                UnknownPersistPtr persist(Locomotor.Pointer);
                GUID clsid;
                persist->GetClassID(&clsid);
                is_jumpjet = memcmp(&clsid, &CLSID_JumpjetLocomotionClass, sizeof(GUID)) == 0;
            }
            if (is_jumpjet) {
                if (unknown_57d) return;
                if (unknown_468 > 0.8) {
                    unknown_slot311(24, false, false);
                } else {
                    unknown_slot311(23, false, false);
                }
                return;
            }
        }
        if (unknown_5c3) {
            unknown_slot311(6, false, false);
        } else {
            unknown_slot311(3, false, false);
        }
    } else {
        if (Sequence == 3 || Sequence == 24 || Sequence == 23) {
            unknown_slot311(0, false, false);
        } else if (Sequence == 6) {
            unknown_slot311(2, false, false);
        } else if (Sequence == 17) {
            unknown_slot311(16, false, false);
        }
        return;
    }
}
