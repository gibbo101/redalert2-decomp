// int HouseClass::Assign_Handicap(int difficulty) (0x004E2E40)
// Takes the difficulty's modifiers from Rules (scaled by the house type's in
// multiplayer; speeds and build time by the game speed bias), restarts the
// team timer and returns the previous difficulty (name after TS).
// @ref ?Frame@@3HA=00a40d2c
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/rules.hpp"

int HouseClass::Assign_Handicap(int difficulty)
{
    int old = unknown_c8;
    unknown_c8 = difficulty;
    if (unknown_game_mode_a3d298) {
        HouseTypeClass *type = Type;
        unknown_d0 = Rules->Diff[difficulty].FirePower * type->FirepowerMult;
        unknown_d8 = Rules->Diff[difficulty].GroundSpeed * Rules->GameSpeedBias * type->GroundspeedMult;
        unknown_e0 = Rules->Diff[difficulty].AirSpeed * Rules->GameSpeedBias * type->AirspeedMult;
        unknown_e8 = Rules->Diff[difficulty].Armor * type->ArmorMult;
        unknown_f0 = Rules->Diff[difficulty].ROF * type->ROFMult;
        unknown_f8 = Rules->Diff[difficulty].Cost * type->CostMult;
        unknown_108 = Rules->Diff[difficulty].RepairDelay;
        unknown_110 = Rules->Diff[difficulty].BuildDelay;
        unknown_100 = Rules->Diff[difficulty].BuildTime * Rules->GameSpeedBias * type->BuildtimeMult;
    } else {
        unknown_d0 = Rules->Diff[difficulty].FirePower;
        unknown_d8 = Rules->Diff[difficulty].GroundSpeed * Rules->GameSpeedBias;
        unknown_e0 = Rules->Diff[difficulty].AirSpeed * Rules->GameSpeedBias;
        unknown_e8 = Rules->Diff[difficulty].Armor;
        unknown_f0 = Rules->Diff[difficulty].ROF;
        unknown_f8 = Rules->Diff[difficulty].Cost;
        unknown_108 = Rules->Diff[difficulty].RepairDelay;
        unknown_110 = Rules->Diff[difficulty].BuildDelay;
        unknown_100 = Rules->Diff[difficulty].BuildTime * Rules->GameSpeedBias;
    }
    unknown_5684 = CDTimerClass<FrameTimerClass>(Rules->TeamDelays[difficulty] + ArrayIndex * 175);
    return old;
}
