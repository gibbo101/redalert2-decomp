// Starts a firing sequence and fires on its configured frame (0x00507530).
#include "shared/infantry.hpp"
#include "shared/techno_map.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref _CLSID_JumpjetLocomotionClass=007a2000
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Direction_To@ObjectClass@@QBE?AUUnknownFacingDir@@PBVAbstractClass@@@Z=005d2730
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ?unknown_4cd9b0@FootClass@@QAEXXZ=004cd9b0
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?Unknown_00476920@UnknownCellClass@@QAEXPBUCoordStruct@@_N11@Z=00476920
extern "C" GUID const CLSID_JumpjetLocomotionClass;
void InfantryClass::Update_Fire_00507530()
{
    if (unknown_228 != 0) {
    int weapon = unknown_slot174(unknown_228);
    if (!unknown_57d) {
        int error = unknown_slot218(unknown_228, weapon, 1);
        switch (error) {
        case 0: {

            if (Type->JumpJet) {
                bool is_jumpjet;
                {
                    UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(Locomotor);
                    GUID clsid;
                    persist.Checked()->GetClassID(&clsid);
                    is_jumpjet = memcmp(&clsid, &CLSID_JumpjetLocomotionClass, sizeof(GUID)) == 0;
                }
                if (is_jumpjet) {
                    unknown_slot311(26, false, false);
                    goto sequence_started;
                }
            }
            if (unknown_5090d0()) {
                unknown_slot311(29, false, false);
            } else if (unknown_5c3) {
                unknown_slot311(8, false, false);
            } else {
                unknown_slot311(4, false, false);
            }
        sequence_started:
            unknown_57d = true;
            unknown_2e0.Set_Current(Direction_To(unknown_228));
            if (unknown_228 == unknown_494) {
                unknown_4cd9b0();
                unknown_slot291();
            }
                } break;
        case 5: {

            if (unknown_6c16f0(weapon) < 0) {
                AbstractClass *target = unknown_228;
                if (target != 0 && target->unknown_14_bit1 && target->Kind_Of() == 15) {
                    if (((ObjectClass *)target)->Health_Ratio() >= Rules->unknown_1360) {
                        unknown_slot220(0);
                    }
                } else {
                    unknown_slot220(0);
                }
            }
                } break;
        case 9:

            unknown_slot252(false);
                    break;
        }

    }
    int fire_frame = Type->FireUp;
    if (unknown_5c3) {
        fire_frame = Type->FireProne;
    }
    if (unknown_57d && StageClass::Stage == fire_frame) {
        weapon = unknown_slot174(unknown_228);
        if (unknown_slot218(unknown_228, weapon, 1) == 0) {
            unknown_slot221(unknown_228, weapon);
        } else {
            unknown_57d = false;
            if (unknown_5c3) {
                unknown_slot311(2, false, false);
            } else if (unknown_5090d0()) {
                unknown_slot311(28, false, false);
            } else {
                unknown_slot311(0, false, false);
            }
        }
        if (unknown_228 != 0 && unknown_slot231(0)->WeaponType->unknown_a8 < Rules->unknown_1328) {
            ((UnknownCellClass *)&Map[unknown_228->Center_Coord()])->Unknown_00476920(&CoordStruct(Coord), true, false, false);
        }
    }
    } else {
        unknown_57d = false;
    }
}
