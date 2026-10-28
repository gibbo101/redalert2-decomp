// void MPCooperative::unknown_slot38() -- 0x005A6040
// Rebuilds the session player list from the players slot 34 saved, keeping those whose name
// is a house's UIName (each saved player's ID becomes that house's index).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
// @ref __wcsicmp=00796318
// @ref _wcscpy=00783689
#include "shared/multiplayer_game_mode.hpp"
#include "shared/house.hpp"
#include "shared/lobby.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/crt_string.hpp"

void MPCooperative::unknown_slot38()
{
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    unknown_session_a3d55c = 0;
    for (int i = 0; i < unknown_players_5c.Count(); i++) {
        for (int h = 0; h < Houses.Count(); h++) {
            if (_wcsicmp(Houses[h]->UIName, unknown_players_5c[i]->Name) == 0) {
                unknown_players_5c[i]->ID = h;
                NodeNameType *entry = new NodeNameType;
                wcscpy(entry->Name, unknown_players_5c[i]->Name);
                entry->unknown_6b = unknown_players_5c[i]->unknown_6b;
                entry->unknown_4b = unknown_players_5c[i]->unknown_4b;
                entry->unknown_53 = unknown_players_5c[i]->unknown_53;
                strcpy(entry->unknown_34, unknown_players_5c[i]->unknown_34);
                entry->unknown_4f = unknown_players_5c[i]->unknown_4f;
                entry->unknown_57 = unknown_players_5c[i]->unknown_57;
                entry->Team = unknown_players_5c[i]->Team;
                entry->unknown_63 = unknown_players_5c[i]->unknown_63;
                entry->unknown_67 = unknown_players_5c[i]->unknown_67;
                entry->unknown_6b = unknown_players_5c[i]->unknown_6b;
                NetNumType net;
                NetNodeType node;
                unsigned short socket;
                unknown_players_5c[i]->Address.Get_Address(net, node, &socket);
                entry->Address.Set_Address(net, node, socket);
                unknown_players_a3fa7c.Add(entry);
                unknown_session_a3d55c++;
                break;
            }
        }
    }
}
