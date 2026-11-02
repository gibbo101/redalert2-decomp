// void ScenarioCheckpoint_004B5A70::Restore_004B5B40() (0x004B5B40)
// Puts a captured checkpoint back: the 50 local variables, the credits scaled by the
// scenario's carry-over factor (capped by its carry-over cap unless -1) as a refund that
// is also added to +0x124, the difficulty, and with TimerInherit a positive remaining
// time restarts the mission timer; then the +0x2304 word.
#include "shared/scenario_checkpoint.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
// @ref ?unknown_6612c0@UnknownIDSource@@QAE_NI_N@Z=006612c0
// @ref ?Refund_Money@HouseClass@@QAEXH@Z=004e5440
// @ref ?Assign_Handicap@HouseClass@@QAEHH@Z=004e2e40

void ScenarioCheckpoint_004B5A70::Restore_004B5B40()
{
    for (int i = 0; i < 50; ++i) {
        unknown_id_source_a3d290->unknown_6612c0(i, Variables[i]);
    }
    int cap = unknown_id_source_a3d290->unknown_1208;
    double money = Credits * unknown_id_source_a3d290->CarryOverMoney;
    if (cap != -1) {
        money = money < (double)cap ? money : (double)cap;
    }
    int credits = (int)money;
    unknown_player_a35db4->Refund_Money(credits);
    unknown_player_a35db4->unknown_124 += credits;
    unknown_player_a35db4->Assign_Handicap(Difficulty);
    if (unknown_id_source_a3d290->unknown_2231) {
        if (TimerRemaining > 0) {
            unknown_id_source_a3d290->MissionTimer = CDTimerClass<FrameTimerClass>(TimerRemaining);
            unknown_id_source_a3d290->MissionTimer.Start();
        }
    }
    unknown_id_source_a3d290->unknown_2304 = unknown_40;
}
