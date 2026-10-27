// void __fastcall TechnoClass::unknown_6d8fd0(TechnoClass *techno, int value) (0x006D8FD0)
// Sets the talk-bubble techno (0x00AC01C4) and its value (0x00AC01C8),
// restarts the talk-bubble timer (0x00AC0168) with Rules TalkBubbleTime and
// reveals around the techno for the player (0x00549C50); without both, it
// clears them and stops the timer at 0 (hypotheses: team script talk
// bubbles, 0x006B2F50).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/system_timer.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_timer_ac0168@@3V?$CDTimerClass@VSystemTimerClass@@@@A=00ac0168
// @ref ?unknown_talk_techno_ac01c4@@3PAVTechnoClass@@A=00ac01c4
// @ref ?unknown_talk_value_ac01c8@@3HA=00ac01c8
// @ref ?Unknown_00549C50@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2222@Z=00549c50

void __fastcall TechnoClass::unknown_6d8fd0(TechnoClass *techno, int value)
{
    if (techno != 0 && value != 0) {
        unknown_talk_value_ac01c8 = value;
        unknown_talk_techno_ac01c4 = techno;
        unknown_timer_ac0168 = Rules->TalkBubbleTime;
        Map.Unknown_00549C50(techno->Center_Coord(), 2, unknown_player_a35db4, false, false, false, true, true);
    } else {
        unknown_talk_value_ac01c8 = 0;
        unknown_talk_techno_ac01c4 = 0;
        unknown_timer_ac0168 = 0;
    }
}
