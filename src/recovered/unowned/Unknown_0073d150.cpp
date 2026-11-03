// Complete original 0073D150,661 body bytes and11 alignment bytes.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_time.hpp"
HWND __fastcall Find_Dialog_00735940(int id);
void __fastcall Unknown_0073FEE0(int unknown, bool update);
extern int unknown_b2ac2c, unknown_b2ab88;
extern long unknown_b2a8a4;

void __fastcall Unknown_0073d150(Wstring const &name, int value)
{
    Wstring nick(name.Length() > 0 ? name : unknown_wstring_b26cb8);
    if (nick == unknown_wstring_b26cb8 && value == 0) {
        HWND dialog = Find_Dialog_00735940(0xc9);
        Unknown_005cd030(dialog, true);
    }
    WOL::User *user = 0;
    for (int index = 0; index < unknown_users_b2a728.Count; ++index) {
        unknown_users_b2a728.Get(user, index);
        if (_stricmp(nick.Peek_Buffer(), user->name) == 0) {
            if (index != -1) {
                unknown_player_b29cf0[index].unknown_20 = value;
                Unknown_0073FEE0(0, false);
            }
            break;
        }
    }
    bool local = unknown_b2ac58 == 1;
    Wstring lower = nick.As_Lower();
    int player_index;
    for (player_index = 0; player_index < unknown_players_a3fa7c.Count(); ++player_index) {
        Wstring player = Narrow_Copy_00771280(unknown_players_a3fa7c[player_index]->Name);
        if (player.As_Lower() == lower) break;
    }
    if (player_index >= unknown_players_a3fa7c.Count()) return;
    unknown_players_a3fa7c[player_index]->unknown_67 = value;
    if (local && Is_Online_Session() && !unknown_b2ac04 && player_index == 1 && unknown_users_b2a728.Count == 2) {
        WOL::User *node;
        WOL::User *head = 0;
        WOL::User copy;
        memset(&copy, 0, sizeof(copy));
        for (int user_index = 0; user_index < unknown_users_b2a728.Count; ++user_index) {
            unknown_users_b2a728.Get_Copy(copy, user_index);
            node = new WOL::User;
            *node = copy;
            node->next = head;
            head = node;
        }
        unknown_b2ac2c = 0;
        unknown_b26898 = 9;
        unknown_b2ab88 = 90;
        unknown_b2a8a4 = time(0);
        unknown_chat_a72cfc->RequestGameStart(head);
        unknown_b2ac04 = true;
        node = head;
        while (node) {
            head = node->next;
            delete node;
            node = head;
        }
    }
    Unknown_0073FEE0(0, false);

}
// @ref ?Find_Dialog_00735940@@YIPAUHWND__@@H@Z=00735940
// @ref ?Unknown_0073FEE0@@YIXH_N@Z=0073fee0
// @ref ?unknown_b2ac2c@@3HA=00b2ac2c
// @ref ?unknown_b2ab88@@3HA=00b2ab88
// @ref ?unknown_b2a8a4@@3JA=00b2a8a4
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
