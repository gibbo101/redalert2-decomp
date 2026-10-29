// void UnknownIDSource::Set_Defaults() (0x0065B830)
// @ref ??_C@_0BB@GBE@GUI?3SkirmishGame?$AA@=007f1e04
#include "shared/id_source.hpp"
#include "shared/abstract_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"
#include "shared/campaign.hpp"

void UnknownIDSource::Set_Defaults()
{
    HomeCell = 98;
    AltHomeCell = 98;
    UniqueID = 1000000;
    Difficulty = 1;
    unknown_610 = 1;
    ElapsedTime = 0;
    ElapsedTime.Stop();
    unknown_620 = 0;
    unknown_620.Stop();
    unknown_62c = 0;
    unknown_630 = false;
    MissionTimer = 0;
    MissionTimer.Stop();
    MissionTimerText = unknown_empty_wide_839d4c;
    MissionTimerLabel = FixedString<32>(unknown_string_83c55c);
    unknown_7f8 = 0;
    unknown_804 = 0;
    unknown_810 = 0;
    unknown_81c = 0;
    unknown_828 = 0;
    Theater = -1;
    IntroMovie = -1;
    BriefMovie = -1;
    WinMovie = -1;
    LoseMovie = -1;
    ActionMovie = -1;
    PostScoreMovie = -1;
    PreMapSelectMovie = -1;
    Theme = -1;
    unknown_11fc = 0;
    CarryOverMoney = 0;
    unknown_1208 = 0;
    Percent = 0;
    unknown_2224 = 0;
    FreeRadar = false;
    unknown_2229 = false;
    unknown_222a = true;
    unknown_222b = true;
    unknown_222c = true;
    unknown_222d = false;
    unknown_222e = false;
    unknown_222f = false;
    EndOfGame = false;
    unknown_2231 = false;
    SkipScore = false;
    OneTimeOnly = false;
    SkipMapSelect = false;
    TruckCrate = false;
    FillSilos = false;
    unknown_2238 = false;
    unknown_2239 = true;
    MultiplayerOnly = false;
    unknown_223c = false;
    unknown_2240 = 0;
    StartingDropships = 0;
    unknown_22a8 = 100;
    unknown_22ac = 100;
    unknown_22b0 = 100;
    AmbientRed = 100;
    AmbientGreen = 100;
    AmbientBlue = 100;
    AmbientGround = 100;
    AmbientLevel = 16;
    IonAmbient = 100;
    IonRed = 0;
    IonGreen = 0;
    IonBlue = 0;
    IonGround = 100;
    IonLevel = 16;
    unknown_22e0 = 200;
    unknown_22e4 = 175;
    unknown_22e8 = 150;
    unknown_22ec = 125;
    unknown_22f0 = 100;
    unknown_22f4 = 100;
    NukeAmbientChangeRate = 1;
    InitTime = 10000;
    unknown_2304 = 0;
    unknown_2306 = false;
    TiberiumDeathToVisceroid = true;
    ParTimeEasy = 3600;
    ParTimeMedium = 3600;
    ParTimeHard = 3600;
    UnderParTitle[0] = 0;
    UnderParMessage[0] = 0;
    OverParTitle[0] = 0;
    OverParMessage[0] = 0;
    LSLoadMessage[0] = 0;
    LSLoadBriefing[0] = 0;
    LS640BriefLocX = 0;
    LS640BriefLocY = 0;
    LS800BriefLocX = 0;
    LS800BriefLocY = 0;
    LS640BkgdName[0] = 0;
    LS800BkgdName[0] = 0;
    AllowableUnits.Clear();
    AllowableUnitMaximums.Clear();
    AllowableUnitCounts.Clear();
    if (unknown_game_mode_a3d298 == 5) {
        wcscpy(unknown_id_source_a3d290->Name, StringTable::Load_String("GUI:SkirmishGame", 0, "D:\\Ra2\\Scenario.CPP", 486));
    }
}
