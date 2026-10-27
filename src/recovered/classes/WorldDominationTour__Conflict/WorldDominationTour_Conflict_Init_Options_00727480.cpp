// Conflict::Init_Options (0x00727480): builds the shared list of battle options.
// @ref ?unknown_game_options_b256c0@@3V?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@A=00b256c0
// @ref ??0?$rc_ptr@VGameOption@WorldDominationTour@@@@QAE@ABVrc_ptr_base@@@Z=00728300
// @ref ??1?$rc_ptr@VFlagGameOption@WorldDominationTour@@@@UAE@XZ=00727c90
// @ref ??1?$rc_ptr@VGameOption@WorldDominationTour@@@@UAE@XZ=00727c80
// @ref ??1?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@UAE@XZ=00727ca0
// @ref ??_C@_09FMPG@WDT?3Bases?$AA@=007fba0c
// @ref ??_C@_0BB@DFIC@WDT?3NotShortGame?$AA@=007fb9dc
// @ref ??_C@_0BC@OEOG@WDT?3NoRedeployMCV?$AA@=007fb9a4
// @ref ??_C@_0BE@EAHD@WDT?3RedeployableMCV?$AA@=007fb9b8
// @ref ??_C@_0L@PNIA@WDT?3Crates?$AA@=007fb998
// @ref ??_C@_0M@HOM@WDT?3NoBases?$AA@=007fba00
// @ref ??_C@_0N@CKNL@WDT?3NoCrates?$AA@=007fb988
// @ref ??_C@_0O@KICH@WDT?3TechLevel?$AA@=007fba18
// @ref ??_C@_0O@OPME@WDT?3ShortGame?$AA@=007fb9f0
// @ref ??_C@_0O@PPNB@WDT?3UnitCount?$AA@=007fb9cc
// @ref ?Add@?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@QAE_NABV?$rc_ptr@VGameOption@WorldDominationTour@@@@@Z=00728270
// @ref ?Create@?$ValueGameOption@E@WorldDominationTour@@SI?AV?$rc_ptr@V?$ValueGameOption@E@WorldDominationTour@@@@HP6IHPBVWDTTerritory@@@ZVWstring@@H@Z=00727c10
// @ref ?Create@MapSizeGameOption@WorldDominationTour@@SI?AV?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@H@Z=00728a60
// @ref ?WDTTerritory_Get_Tech_Level@@YIHPBVWDTTerritory@@@Z=00727b80
// @ref ?WDTTerritory_Get_Unit_Count@@YIHPBVWDTTerritory@@@Z=00727b70
// @ref ??_7?$rc_ptr@V?$ValueGameOption@E@WorldDominationTour@@@@6B@=007af0d4
// @ref ??_7?$rc_ptr@VFlagGameOption@WorldDominationTour@@@@6B@=007af0cc
// @ref ??_7?$rc_ptr@VGameOption@WorldDominationTour@@@@6B@=007af0dc
// @ref ??_7?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@6B@=007af0f8
// @ref ??_G?$rc_ptr@V?$ValueGameOption@E@WorldDominationTour@@@@UAEPAXI@Z=00727cf0
// @ref ??_G?$rc_ptr@VFlagGameOption@WorldDominationTour@@@@UAEPAXI@Z=00727d20
// @ref ??_G?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@UAEPAXI@Z=00727d50
// @ref ??_7GameOption@WorldDominationTour@@6B@=007af118
// @ref ?Clear@?$VectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@UAEXXZ=007280c0
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
#include "shared/wdt_game_options.hpp"

int __fastcall WDTTerritory_Get_Unit_Count(WDTTerritory const *territory);
int __fastcall WDTTerritory_Get_Tech_Level(WDTTerritory const *territory);

namespace WorldDominationTour {

void __fastcall Conflict::Init_Options()
{
    Clear_Options();
    unknown_game_options_b256c0.Add(rc_ptr<GameOption>(ValueGameOption<unsigned char>::Create(0x10000, WDTTerritory_Get_Tech_Level, Wstring("WDT:TechLevel"), 0)));
    unknown_game_options_b256c0.Add(rc_ptr<GameOption>(FlagGameOption::Create(0x10, Wstring("WDT:NoBases"), 0, Wstring("WDT:Bases"), 1)));
    unknown_game_options_b256c0.Add(rc_ptr<GameOption>(FlagGameOption::Create(0x400, Wstring("WDT:NotShortGame"), 1, Wstring("WDT:ShortGame"), 0)));
    unknown_game_options_b256c0.Add(rc_ptr<GameOption>(ValueGameOption<unsigned char>::Create(0x8000, WDTTerritory_Get_Unit_Count, Wstring("WDT:UnitCount"), 0)));
    unknown_game_options_b256c0.Add(rc_ptr<GameOption>(FlagGameOption::Create(0x20, Wstring("WDT:NoRedeployMCV"), 1, Wstring("WDT:RedeployableMCV"), 0)));
    unknown_game_options_b256c0.Add(rc_ptr<GameOption>(FlagGameOption::Create(0x100, Wstring("WDT:NoCrates"), 1, Wstring("WDT:Crates"), 1)));
    unknown_game_options_b256c0.Add(MapSizeGameOption::Create(0xc000000));
}

}
