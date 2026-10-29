// Wstring const &__fastcall Faction_Code(int faction) -- 0x007686D0
// The two-letter code of a faction ("NA", "EU", "AS", else "XX").
#include "shared/world_domination_tour.hpp"
#include "shared/wstring.hpp"

// @ref ??_C@_02GHFJ@NA?$AA@=008004d4
// @ref ??_C@_02OKNO@EU?$AA@=008004d0
// @ref ??_C@_02EPAG@AS?$AA@=008004cc
// @ref ??_C@_02CNFA@XX?$AA@=008004c8
// @ref _?$S52@?1??Faction_Code@@YIABVWstring@@H@Z@4EA=00b2acd0
// @ref _?na@?1??Faction_Code@@YIABVWstring@@H@Z@4V2@A=00b2ace0
// @ref _?eu@?1??Faction_Code@@YIABVWstring@@H@Z@4V2@A=00b2ace4
// @ref _?as@?1??Faction_Code@@YIABVWstring@@H@Z@4V2@A=00b2ad34
// @ref _?unknown@?3??Faction_Code@@YIABVWstring@@H@Z@4V2@A=00b2acd4
// @ref _$E53=007687f0
// @ref _$E54=007687e0
// @ref _$E55=007687d0
// @ref _$E56=007687c0
Wstring const &__fastcall Faction_Code(int faction)
{
    static Wstring na("NA");
    static Wstring eu("EU");
    static Wstring as("AS");
    switch (faction) {
    case 1:
        return na;
    case 2:
        return eu;
    case 3:
        return as;
    default:
        static Wstring unknown("XX");
        return unknown;
    }
}
