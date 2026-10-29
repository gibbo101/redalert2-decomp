// Wstring const &__fastcall Faction_Name(int faction) -- 0x007685A0
// The faction name of a faction number ("DIS", "ALL", "SOV", else "xx").
#include "shared/wdt_voices.hpp"
#include "shared/wstring.hpp"

// @ref ??_C@_03DHKC@DIS?$AA@=008004c4
// @ref ??_C@_03MJMD@ALL?$AA@=007ccc18
// @ref ??_C@_03NPJN@SOV?$AA@=008004c0
// @ref ??_C@_02KKOC@xx?$AA@=008004bc
// @ref _?$S47@?1??Faction_Name@@YIABVWstring@@H@Z@4EA=00b2ad24
// @ref _?dis@?1??Faction_Name@@YIABVWstring@@H@Z@4V2@A=00b2ad38
// @ref _?all@?1??Faction_Name@@YIABVWstring@@H@Z@4V2@A=00b2ad20
// @ref _?sov@?1??Faction_Name@@YIABVWstring@@H@Z@4V2@A=00b2ad48
// @ref _?unknown@?3??Faction_Name@@YIABVWstring@@H@Z@4V2@A=00b2ad08
// @ref _$E48=007686c0
// @ref _$E49=007686b0
// @ref _$E50=007686a0
// @ref _$E51=00768690
// Never inlined by the original (Theater_Choice_Menu 0x00768DD0 calls it).
#pragma auto_inline(off)
Wstring const &__fastcall Faction_Name(int faction)
{
    static Wstring dis("DIS");
    static Wstring all("ALL");
    static Wstring sov("SOV");
    switch (faction) {
    case 1:
        return dis;
    case 2:
        return all;
    case 3:
        return sov;
    default:
        static Wstring unknown("xx");
        return unknown;
    }
}
#pragma auto_inline(on)
