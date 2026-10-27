// bool MultiplayerSiege::unknown_slot5(WideString *message) -- 0x005AB640
// Slot 5 (the team check before a game): after the base check
// (0x005B73A0), requires exactly one defender (team 1), at least one
// attacker (team 2) and no other team numbers besides 0; otherwise sets the
// localized reason in *message and fails.
#include "shared/string_table.hpp"
// @ref ?unknown_slot5@MultiplayerGameMode@@UAE_NPAVWideString@@@Z=005b73a0
// @ref ??4WideString@@QAEAAV0@PBG@Z=0076fb70
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BD@IPKL@D?3?2Ra2?2MPSiege?4cpp?$AA@=007e56b4
// @ref ??_C@_0BD@JCEM@MP?3OnlyOneBeseiged?$AA@=007e5680
// @ref ??_C@_0O@MIIP@MP?3NoDefender?$AA@=007e56a4
// @ref ??_C@_0P@HPML@MP?3NoAttackers?$AA@=007e5670
// @ref ??_C@_0P@KHFM@MP?3IllegalTeam?$AA@=007e5694

bool MultiplayerSiege::unknown_slot5(WideString *message)
{
    if (!MultiplayerGameMode::unknown_slot5(message)) {
        return false;
    }
    bool defender = false;
    int attackers = 0;
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        switch (unknown_players_a3fa7c[index]->Team) {
        case 0:
            break;
        case 1:
            if (defender) {
                *message = StringTable::Load_String("MP:OnlyOneBeseiged", 0, "D:\\Ra2\\MPSiege.cpp", 0x33);
                return false;
            }
            defender = true;
            break;
        case 2:
            attackers++;
            break;
        default:
            *message = StringTable::Load_String("MP:IllegalTeam", 0, "D:\\Ra2\\MPSiege.cpp", 0x3c);
            return false;
        }
    }
    if (!defender) {
        *message = StringTable::Load_String("MP:NoDefender", 0, "D:\\Ra2\\MPSiege.cpp", 0x41);
        return false;
    }
    if (attackers < 1) {
        *message = StringTable::Load_String("MP:NoAttackers", 0, "D:\\Ra2\\MPSiege.cpp", 0x46);
        return false;
    }
    return true;
}
