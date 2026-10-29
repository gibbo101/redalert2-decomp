// UnknownGameOptions (the 0x7C option block; session +0x13C, +0x1B8, +0x234).
#include "shared/session_state.hpp"

// The defaults: credits 10000, ten units, the five flags set, the rest 0.
UnknownGameOptions::UnknownGameOptions() :
    GameMode(0),
    ScenIndex(0),
    GameSpeed(0),
    Credits(10000),
    UnitCount(10),
    ShortGame(true),
    SuperWeaponsAllowed(true),
    BuildOffAlly(true),
    MCVRepacks(true),
    CratesAppear(true)
{
    for (int i = 0; i < 8; i++) {
        Slots[i][0] = 0;
        Slots[i][1] = 0;
        Slots[i][2] = 0;
    }
}
