// bool MPCooperative::unknown_slot21() -- 0x005A3960
// Picks the computer players' houses and colours for every map of the selected campaign record
// (slot 23/24 houses; the players' colours first, random free colours for the rest) into
// unknown_1a8/unknown_268 and sends them as a "C1,<maps>,<house>,<colour>..." game options text.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
// @ref _sprintf=007820f4
// @ref ?Get_Color_0066e2b0@NodeNameType@@QAEHXZ=0066e2b0
// @ref ?unknown_colors_a71118@@3PAHA=00a71118
// @ref ??_C@_05GNBO@C1?0?$CFd?$AA@=007e357c
// @ref ??_C@_06FOAE@?0?$CFd?0?$CFd?$AA@=007e3574
// @ref ??_C@_0CM@BBG@?$EA?$EA?$EA?$EA?5Sending?5campaign?5game?5AI?5se@=007e3548
// @ref ??_C@_0L@CIDM@?$EA?$EA?$EA?$EA?5Sent?6?$AA@=007d5024
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/id_source.hpp"
#include "shared/lobby.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"

bool MPCooperative::unknown_slot21()
{
    UnknownDescriptionRecord_00490E00 *record;
    unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
    char message[400];
    sprintf(message, "C1,%d", record->MapCount);
    for (int list = 0; list < 8; list++) {
        int length = unknown_1a8[list].Length();
        unknown_1a8[list].Clear();
        unknown_1a8[list].Resize(length);
        length = unknown_268[list].Length();
        unknown_268[list].Clear();
        unknown_268[list].Resize(length);
    }
    int players = unknown_players_a3fa7c.Count();
    for (int map = 0; map < record->MapCount; map++) {
        int i;
        for (i = 0; i < 8; i++) {
            unknown_colors_a71118[i] = -2;
        }
        int count = unknown_players_a3fa7c.Count();
        for (i = 0; i < count; i++) {
            unknown_colors_a71118[i] = unknown_players_a3fa7c[i]->Get_Color_0066e2b0();
        }
        for (int slot = 0; slot < 8; slot++) {
            if (slot < players) {
                unknown_1a8[slot].Add(unknown_slot23());
                unknown_268[slot].Add(unknown_colors_a71118[slot]);
            } else {
                unknown_1a8[slot].Add(unknown_slot24());
                int color;
                bool taken;
                do {
                    color = unknown_id_source_a3d290->RandomNumber(0, 7);
                    taken = false;
                    if (color != -2) {
                        for (i = 0; i < 8; i++) {
                            if (unknown_colors_a71118[i] == color) {
                                taken = true;
                                break;
                            }
                        }
                    }
                } while (taken);
                unknown_colors_a71118[slot] = color;
                unknown_268[slot].Add(color);
            }
            char text[16];
            sprintf(text, ",%d,%d", unknown_1a8[slot][map], unknown_268[slot][map]);
            strcat(message, text);
        }
    }
    Debug_Printf("@@@@ Sending campaign game AI settings: %s\n", message);
    Send_Game_Options_005c3c60(message);
    Debug_Printf("@@@@ Sent\n");
    return true;
}
