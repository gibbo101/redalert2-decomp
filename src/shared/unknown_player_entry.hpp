#ifndef RA2_SHARED_UNKNOWN_PLAYER_ENTRY_HPP
#define RA2_SHARED_UNKNOWN_PLAYER_ENTRY_HPP
#include "shared/vector_class.hpp"
#include "shared/ipx_address.hpp"
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif
#pragma pack(push, 1)
// Packed 0x75-byte player entry. The name is from RTTI: MPCooperative's saved player list (+0x5C) is a
// DynamicVectorClass<NodeNameType *> (VectorClass vtable 0x007A6884, RTTI .?AV?$VectorClass@PAUNodeNameType@@@@)
// whose elements are copied field by field into the session list (0x005A6040).
struct NodeNameType {
    wchar_t Name[20];
    IPXAddressClass Address;
    union {
        char unknown_34[0x4b - 0x34];   // +0x34 a narrow string (copied with strcpy)
        struct {
            unsigned char IsOpen;       // +0x34 the game is open (Red Alert's Game.IsOpen)
            unsigned long LastTime;     // +0x35 the last time the game was heard from
        } Game;                         // an entry of unknown_games_a3fa64
        struct {
            unsigned long LastTime;     // +0x34 the last time the player was heard from (0: not yet)
            unsigned char LastChance;   // +0x38 a NET_CHAT_REQUEST was sent before the removal
        } Chat;                         // an entry of unknown_chat_a3fa4c
    };
    int unknown_4b;                 // +0x4B the country (HouseTypes index; -3: random, read as 0 by Read_Scenario_INI)
    int unknown_4f;                 // +0x4F
    int unknown_53;                 // +0x53 the colour (lowest first gets the first house; Assign_Houses)
    int unknown_57;                 // +0x57 (-2 with +0x53 -1: the colour reads as random)
    int Team;
    int ID;                         // +0x5F (IPXManagerClass compares it with a node id; Assign_Houses stores the house index)
    int unknown_63;                 // +0x63
    int unknown_67;                 // +0x67 (cleared by 0x005C9700 for every entry but the host's)
    int unknown_6b;                 // +0x6B
    int unknown_map_state_6f;       // +0x6F the player's map state (0: no map, 2: transfer, 1: the host; 0x005C3F00)
    char unknown_73[0x75 - 0x73];
    int unknown_66e290();
    int unknown_66e2a0();
    int Get_Color_0066e2b0();          // 0x0066E2B0 the colour (+0x53; -2 when +0x57 is -2 and +0x53 is -1)
    int Get_Color_0066e2a0(); // Same actual accessor; original +53/+57 sentinel operation.
    void unknown_66e2d0(int value);
    void unknown_66e300(int value);
};
#pragma pack(pop)
extern DynamicVectorClass<NodeNameType *> unknown_players_a3fa7c;
// The entry of each player row of the setup dialogs (0x00A3FA98, eight), and the
// entry the dialogs compare a row against (0x00A72D44; meaning not recovered).
extern NodeNameType *unknown_player_slots_a3fa98[8];
extern NodeNameType *unknown_player_a72d44;
#endif
