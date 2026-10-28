// void TechnoClass::Init() (0x006C1C50, slot 9)
// Records whether the owner is the player (+0x372); with a type, makes the
// owned helpers its type and primary weapon's warhead call for: a spawn
// manager for Spawns (+0x238), a capture manager for a MindControl warhead
// (+0x230), a parasite for a Parasite warhead on non-buildings (FootClass
// +0x588) and a temporal for a Temporal warhead (+0x208, taking the weapon's
// +0xA4); a permanently disguised type takes its owner as the disguise house
// and the rules' disguise (+0xB6C, or +0xB70 when the owner's +0x130 is set);
// copies the turret and barrel recoil timing and resets +0x3EC/+0x3F0.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/capture_manager.hpp"
#include "shared/parasite.hpp"
#include "shared/temporal.hpp"
// The infantry type (for the disguise types): InfantryClass itself comes from shared/infantry.hpp.
#define RA2_INFANTRY_FULL
#include "shared/infantry_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0SpawnManagerClass@@QAE@PAVTechnoClass@@PAVAircraftTypeClass@@HHH@Z=00689710
// @ref ??0CaptureManagerClass@@QAE@PAVTechnoClass@@@Z=00467db0
// @ref ??0ParasiteClass@@QAE@PAVAbstractClass@@@Z=00606240
// @ref ??0TemporalClass@@QAE@PAVTechnoClass@@@Z=006e1f80

// Takes a type's recoil timing (travel and the three frame counts).
inline void Copy_Recoil(UnknownTechnoBlock &block, RecoilControl const &data)
{
    block.unknown_00 = data.Travel;
    block.unknown_04 = data.CompressFrames;
    block.unknown_08 = data.RecoverFrames;
    block.unknown_0c = data.HoldFrames;
}

void TechnoClass::Init()
{
    if (House != 0) {
        if (unknown_player_a35db4 == House) {
            unknown_372 = true;
        } else {
            unknown_372 = false;
        }
    }
    if (unknown_slot32() == 0) {
        return;
    }
    if (unknown_slot32()->Spawns != 0) {
        SpawnManager = new SpawnManagerClass(this, unknown_slot32()->Spawns, unknown_slot32()->SpawnsNumber,
            unknown_slot32()->SpawnRegenRate, unknown_slot32()->SpawnReloadRate);
    }
    if (unknown_slot231(0)->WeaponType != 0 && unknown_slot231(0)->WeaponType->Warhead->MindControl) {
        unknown_230 = new CaptureManagerClass(this);
    }
    if (Kind_Of() != 6 && unknown_slot231(0)->WeaponType != 0 && unknown_slot231(0)->WeaponType->Warhead->Parasite) {
        ((FootClass *)this)->unknown_588 = new ParasiteClass(this);
    }
    if (unknown_slot231(0)->WeaponType != 0 && unknown_slot231(0)->WeaponType->Warhead->Temporal) {
        unknown_208 = (UnknownTechno208 *)new TemporalClass(this);
        ((TemporalClass *)unknown_208)->unknown_4c = unknown_slot231(0)->WeaponType->unknown_a4;
    }
    if (unknown_slot32()->CanDisguise && unknown_slot32()->PermaDisguise) {
        unknown_170 = true;
        unknown_410 = House;
        if (House->unknown_130 == 0) {
            unknown_40c = Rules->unknown_b6c;
        } else {
            unknown_40c = Rules->unknown_b70;
        }
    }
    Copy_Recoil(unknown_330, unknown_slot32()->TurretAnimData);
    Copy_Recoil(unknown_350, unknown_slot32()->BarrelAnimData);
    unknown_3ec = 1;
    unknown_3f0 = 0;
}
