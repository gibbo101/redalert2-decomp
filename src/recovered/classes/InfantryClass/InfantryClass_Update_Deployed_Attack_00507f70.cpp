// Deployed attack and radiation update (0x00507F70).
#include "shared/infantry.hpp"
#include "shared/radsite.hpp"
#include "shared/cell.hpp"
#include "shared/techno_map.hpp"
#include "shared/weapon_type.hpp"
// @ref ?Unknown_0047CE40@RadSiteCell@@QAEPAVRadSiteClass@@XZ=0047ce40
// @ref ?Get_Current_Level@RadSiteClass@@QBEHXZ=006375d0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
inline int Infantry_Deployment_Radiation_Threshold(WeaponTypeClass const &weapon)
{
    return weapon.unknown_12c / 3;
}
int InfantryClass::Update_Deployed_Attack_00507f70()
{
    if (unknown_5090d0()) {
        if (Type->UndeployDelay > -1) {
            unknown_slot311(31, false, false);
            return Type->DoControls[31].Count;
        }
        if (Type->DeployFire) {
            if (Type->ImmuneToRadiation) {
                RadSiteClass *site = reinterpret_cast<RadSiteCell *>(&Map[unknown_slot104()])->Unknown_0047CE40();
                int threshold = Infantry_Deployment_Radiation_Threshold(*unknown_slot231(1)->WeaponType);
                if (site == 0 || site->Get_Current_Level() < threshold) {
                    unknown_slot220(&Map[unknown_slot104()]);
                    if (unknown_slot218(unknown_228, 1, 1) == 0) {
                        // Slot221's existing int argument carries the same 32-bit target pointer.
                        unknown_slot221(reinterpret_cast<int>(unknown_228), 1);
                        unknown_slot220(0);
                        unknown_slot311(29, false, false);
                        return Type->DoControls[29].Count;
                    }
                    unknown_slot220(0);
                }
                int delay = int(Control()->unknown_10 * 900.0);
                return delay + unknown_id_source_a3d290->Random()(10, 20);
            }
            unknown_slot240();
            int delay = int(Control()->unknown_10 * 900.0);
            return delay + unknown_id_source_a3d290->Random()(0, 2);
        }
    } else {
        if (!Owning_House()->Unknown_004F52F0() && Type->Deployer && Type->DeployFire &&
            Type->UndeployDelay <= -1 && unknown_494 == 0 &&
            Rules->AIAutoDeployFrameDelay[House->unknown_c8] + unknown_ac < Frame) {
            if (unknown_1b0 != 0) {
                if (Coord_Cell(unknown_1b0->Center_Coord()) != Coord_Cell(Center_Coord())) {
                    return -1;
                }
            }
            if (!Type->ImmuneToRadiation) {
                if (!Locomotor.Checked()->Is_Moving()) {
                    unknown_slot311(27, false, false);
                    return Type->DoControls[27].Count;
                }
                Locomotor.Checked()->Stop_Moving();
                unknown_5cc = true;
                int delay = int(Control()->unknown_10 * 900.0);
                return delay + unknown_id_source_a3d290->Random()(0, 2);
            }
        }
    }
    return -1;
}
