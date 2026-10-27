#ifndef RA2_SHARED_UNKNOWN_PLAYER_ENTRY_HPP
#define RA2_SHARED_UNKNOWN_PLAYER_ENTRY_HPP
#include "shared/vector_class.hpp"
#include "shared/ipx_address.hpp"
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif
#pragma pack(push, 1)
// Packed 0x75-byte player entry: original name has not been identified.
struct UnknownPlayerEntry {
    wchar_t Name[20];
    IPXAddressClass Address;
    char unknown_34[0x5b - 0x34];
    int Team;
    int unknown_5f;
    char unknown_63[0x75 - 0x63];
    int unknown_66e290();
    int unknown_66e2a0();
    int Get_Color_0066e2a0(); // Same actual accessor; original +53/+57 sentinel operation.
    void unknown_66e2d0(int value);
    void unknown_66e300(int value);
};
#pragma pack(pop)
extern DynamicVectorClass<UnknownPlayerEntry *> unknown_players_a3fa7c;
#endif
