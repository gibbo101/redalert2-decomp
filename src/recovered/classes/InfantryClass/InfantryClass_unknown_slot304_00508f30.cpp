// void InfantryClass::unknown_slot304() (0x00508F30, slot 304)
// With a target (+0x228): FootClass 0x004C4C30 unless deploying; then, for
// owners failing HouseClass 0x004F52F0, Deployer + DeployFire types whose
// DeployFireWeapon has a type without +0x126: while deploying, sequence 31
// when slot 212 refuses the target; otherwise, once slot 212 accepts it,
// sequence 27 when standing, or stop the locomotor, set +0x5CC and draw
// from the scenario's random generator.
#include "shared/infantry.hpp"
// @ref ?unknown_4c4c30@FootClass@@QAEXXZ=004c4c30
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

void InfantryClass::unknown_slot304()
{
    if (unknown_228 == 0) {
        return;
    }
    if (!unknown_5090d0()) {
        unknown_4c4c30();
    }
    if (Owning_House()->Unknown_004F52F0()) {
        return;
    }
    if (!Type->Deployer || !Type->DeployFire) {
        return;
    }
    int weapon = Type->DeployFireWeapon;
    bool in_range = unknown_slot212(unknown_228, weapon);
    WeaponTypeClass *weapon_type = unknown_slot231(weapon)->WeaponType;
    if (weapon_type == 0 || weapon_type->unknown_126) {
        return;
    }
    if (unknown_5090d0()) {
        if (!in_range) {
            unknown_slot311(31, 0, 0);
        }
        return;
    }
    if (!in_range) {
        return;
    }
    if (!Locomotor.Checked()->Is_Moving()) {
        unknown_slot311(27, 0, 0);
        return;
    }
    Locomotor.Checked()->Stop_Moving();
    unknown_5cc = true;
    Control();
    unknown_id_source_a3d290->Random()(0, 2);   // the scenario's Random() (src/shared/abstract.hpp)
}
