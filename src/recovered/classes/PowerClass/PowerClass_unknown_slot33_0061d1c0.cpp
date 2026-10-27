// wchar_t const *PowerClass::unknown_slot33(int id) (0x0061D1C0, slot 33)
// Help text of a button: the power bar (id 999) shows the player's power
// output and drain; other ids are the radar's.
#include "shared/power.hpp"
// @ref ?unknown_slot33@RadarClass@@UAEPBGH@Z=00634aa0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_text_a767e0@@3PAGA=00a767e0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ??_C@_0BA@JNFD@TXT_POWER_DRAIN?$AA@=007ebf18
// @ref ??_C@_0BB@EJEP@D?3?2Ra2?2Power?4CPP?$AA@=007ebf28

wchar_t const *PowerClass::unknown_slot33(int id)
{
    if (id == 999) {
        swprintf(unknown_text_a767e0, StringTable::Load_String("TXT_POWER_DRAIN", 0, "D:\\Ra2\\Power.CPP", 662),
                 unknown_player_a35db4->Power, unknown_player_a35db4->Drain);
        return unknown_text_a767e0;
    }
    return RadarClass::unknown_slot33(id);
}
