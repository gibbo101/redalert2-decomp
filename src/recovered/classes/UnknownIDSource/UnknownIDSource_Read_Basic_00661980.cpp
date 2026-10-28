// bool UnknownIDSource::Read_Basic(CCINIClass &ini) (0x00661980)
// Reads the scenario's [Basic] settings (the special options, the next
// scenarios, the movies, the flags, the carried money capped at 1.0, the
// loadout lists, whose limits and counts are padded to the type count), the
// local variables, the par times and texts ([Ranking]) and the lighting
// levels ([Lighting], stored in hundredths or thousandths; the ion levels
// default to the normal ones). Then the player's house: by [Basic] Player in
// a normal game, else through 0x0065FBB0. Reports the loading progress
// (55, 58, 60 percent); always true.
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ??8?$VectorClass@PAVTechnoTypeClass@@@@UBE_NABV0@@Z=0046d400
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??_7?$TypeList@PAVTechnoTypeClass@@@@6B@=0079da34
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_7?$VectorClass@PAVTechnoTypeClass@@@@6B@=0079da14
// @ref ??_C@_03GOGG@Red?$AA@=007d61f8
// @ref ??_C@_03JKEC@Win?$AA@=007f2628
// @ref ??_C@_04KPAE@Blue?$AA@=007d649c
// @ref ??_C@_04NLLM@Lose?$AA@=007f2620
// @ref ??_C@_05DKMC@Green?$AA@=007d61fc
// @ref ??_C@_05FGDF@Basic?$AA@=007e1a50
// @ref ??_C@_05JGCF@Brief?$AA@=007f1e58
// @ref ??_C@_05MDNJ@Intro?$AA@=007d9d98
// @ref ??_C@_05PDLI@Theme?$AA@=007d9d6c
// @ref ??_C@_05PGGH@Level?$AA@=007d1374
// @ref ??_C@_06FJFL@IonRed?$AA@=007e1a08
// @ref ??_C@_06HJOA@Player?$AA@=007e1a58
// @ref ??_C@_06NMFG@Action?$AA@=007cdcc8
// @ref ??_C@_06PNBI@Ground?$AA@=007d39d4
// @ref ??_C@_07BBAD@Ambient?$AA@=007e1a48
// @ref ??_C@_07BJKM@Percent?$AA@=007f253c
// @ref ??_C@_07DFFL@Ranking?$AA@=007f2464
// @ref ??_C@_07FDD@IonBlue?$AA@=007e19f4
// @ref ??_C@_07HCDH@CivEvac?$AA@=007f2478
// @ref ??_C@_08DCMN@IonLevel?$AA@=007e19dc
// @ref ??_C@_08FLNN@Lighting?$AA@=007e1a3c
// @ref ??_C@_08GAKH@HomeCell?$AA@=007f248c
// @ref ??_C@_08POGI@IonGreen?$AA@=007e19fc
// @ref ??_C@_09GAOA@PostScore?$AA@=007f2614
// @ref ??_C@_09ICJC@FreeRadar?$AA@=007f2498
// @ref ??_C@_09IJNJ@FillSilos?$AA@=007f255c
// @ref ??_C@_09JANO@SkipScore?$AA@=007f259c
// @ref ??_C@_09MBFO@EndOfGame?$AA@=007f25d8
// @ref ??_C@_09OMNM@IonGround?$AA@=007e19e8
// @ref ??_C@_0BA@DCOP@UnderParMessage?$AA@=007f23fc
// @ref ??_C@_0BA@FAHB@AltNextScenario?$AA@=007f262c
// @ref ??_C@_0BA@PMIO@MultiplayerOnly?$AA@=007f25f4
// @ref ??_C@_0BB@HABF@IceGrowthEnabled?$AA@=007f24c0
// @ref ??_C@_0BC@DPAI@StartingDropships?$AA@=007f2528
// @ref ??_C@_0BC@MBMM@VeinGrowthEnabled?$AA@=007f24d4
// @ref ??_C@_0BD@GLGO@GUI?3NoOverParTitle?$AA@=007f23e8
// @ref ??_C@_0BE@KMLN@GUI?3NoUnderParTitle?$AA@=007f2434
// @ref ??_C@_0BF@GGMC@GUI?3NoOverParMessage?$AA@=007f23c0
// @ref ??_C@_0BG@FMEK@AllowableUnitMaximums?$AA@=007f2500
// @ref ??_C@_0BG@HKNP@TiberiumGrowthEnabled?$AA@=007f24e8
// @ref ??_C@_0BG@IDOP@GUI?3NoUnderParMessage?$AA@=007f240c
// @ref ??_C@_0BG@MPCE@NukeAmbientChangeRate?$AA@=007f2398
// @ref ??_C@_0BH@OBEA@IgnoreGlobalAITriggers?$AA@=007f2544
// @ref ??_C@_0BJ@BOHF@TiberiumDeathToVisceroid?$AA@=007f24a4
// @ref ??_C@_0L@ECCI@TruckCrate?$AA@=007f2574
// @ref ??_C@_0L@GJBC@IonAmbient?$AA@=007e1a10
// @ref ??_C@_0L@KNN@TrainCrate?$AA@=007f2568
// @ref ??_C@_0M@BDFB@ParTimeEasy?$AA@=007f246c
// @ref ??_C@_0M@DABD@OneTimeOnly?$AA@=007f2590
// @ref ??_C@_0M@GCHC@ParTimeHard?$AA@=007f2448
// @ref ??_C@_0M@JGLE@AltHomeCell?$AA@=007f2480
// @ref ??_C@_0N@DMMM@OverParTitle?$AA@=007f23d8
// @ref ??_C@_0N@EOFH@TimerInherit?$AA@=007f25e4
// @ref ??_C@_0N@ICND@NextScenario?$AA@=007f263c
// @ref ??_C@_0N@INIA@PreMapSelect?$AA@=007f2604
// @ref ??_C@_0N@JPJG@NewINIFormat?$AA@=007f25c8
// @ref ??_C@_0N@KKMK@CarryOverCap?$AA@=007f25a8
// @ref ??_C@_0O@CLFP@ParTimeMedium?$AA@=007f2454
// @ref ??_C@_0O@GPN@SkipMapSelect?$AA@=007f2580
// @ref ??_C@_0O@MIOK@UnderParTitle?$AA@=007f2424
// @ref ??_C@_0P@GGKG@OverParMessage?$AA@=007f23b0
// @ref ??_C@_0P@IMA@CarryOverMoney?$AA@=007f25b8
// @ref ??_C@_0P@JBNN@AllowableUnits?$AA@=007f2518
// @ref ??_G?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_G?$TypeList@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046ceb0
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046dac0
// @ref ?Assign_Houses_0065fbb0@@YAXXZ=0065fbb0
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046cce0
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?Clear@?$VectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046d4f0
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?Fetch@?$VectorClass@PAVTechnoTypeClass@@@@UBEPAVTechnoTypeClass@@H@Z=0046cd30
// @ref ?Get_Time@INIClass@@QBEHPBD0H@Z=00510460
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d630
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046cd10
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d520
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046d560
// @ref ?Loading_Progress_00672160@UnknownSessionState@@QAEXH@Z=00672160
// @ref ?Read_Variables@UnknownIDSource@@QAE_NAAVCCINIClass@@@Z=00661770
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d580
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
// @ref ?Resize@?$VectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d440
// @ref ?Reset_Light_Converts_00529720@@YAXXZ=00529720
// @ref __ftol=0077f110
// @ref __real@8@3ff8a3d70a3d70a3d800=0079c518
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@4005c800000000000000=0079b7f0
// @ref __real@8@4008fa00000000000000=0079d2e0
#include "shared/id_source.hpp"
#include "shared/unknown_loadout.hpp"
#include "shared/special.hpp"
#include "shared/ccini_class.hpp"
#include "shared/shape_file.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/house.hpp"
#include "shared/win32_api.hpp"
#include "shared/unknown_globals.hpp"


// Westwood-style macro: each operand is evaluated where it appears (the
// parenthesized operands are load-bearing, VC6_MATCHING_NOTES).
#define Min(a, b) ((a) < (b) ? (a) : (b))

bool UnknownIDSource::Read_Basic(CCINIClass &ini)
{
    Special().Read_INI(ini);
    ini.Get_String("Basic", "NextScenario", NextScenario, NextScenario, sizeof(NextScenario));
    ini.Get_String("Basic", "AltNextScenario", AltNextScenario, AltNextScenario, sizeof(AltNextScenario));
    IntroMovie = ini.Get_Listed_Name("Basic", "Intro", IntroMovie);
    BriefMovie = ini.Get_Listed_Name("Basic", "Brief", BriefMovie);
    WinMovie = ini.Get_Listed_Name("Basic", "Win", WinMovie);
    LoseMovie = ini.Get_Listed_Name("Basic", "Lose", LoseMovie);
    ActionMovie = ini.Get_Listed_Name("Basic", "Action", ActionMovie);
    PostScoreMovie = ini.Get_Listed_Name("Basic", "PostScore", PostScoreMovie);
    PreMapSelectMovie = ini.Get_Listed_Name("Basic", "PreMapSelect", PreMapSelectMovie);
    MultiplayerOnly = ini.Get_Bool("Basic", "MultiplayerOnly", MultiplayerOnly);
    unknown_2231 = ini.Get_Bool("Basic", "TimerInherit", unknown_2231);
    EndOfGame = ini.Get_Bool("Basic", "EndOfGame", EndOfGame);
    Theme = ini.Get_ThemeType("Basic", "Theme", Theme);
    unknown_ini_format_a40d24 = ini.Get_Int("Basic", "NewINIFormat", 0);
    CarryOverMoney = ini.Get_Double("Basic", "CarryOverMoney", CarryOverMoney);
    CarryOverMoney = Min(CarryOverMoney, 1.0);
    unknown_1208 = ini.Get_Int("Basic", "CarryOverCap", unknown_1208);
    SkipScore = ini.Get_Bool("Basic", "SkipScore", SkipScore);
    OneTimeOnly = ini.Get_Bool("Basic", "OneTimeOnly", OneTimeOnly);
    SkipMapSelect = ini.Get_Bool("Basic", "SkipMapSelect", SkipMapSelect);
    TruckCrate = ini.Get_Bool("Basic", "TruckCrate", TruckCrate);
    unknown_2229 = ini.Get_Bool("Basic", "TrainCrate", unknown_2229);
    FillSilos = ini.Get_Bool("Basic", "FillSilos", FillSilos);
    unknown_2238 = ini.Get_Bool("Basic", "IgnoreGlobalAITriggers", unknown_2238);
    Percent = ini.Get_Int("Basic", "Percent", Percent);
    StartingDropships = ini.Get_Int("Basic", "StartingDropships", StartingDropships);
    AllowableUnits = ini.Get_Techno_List("Basic", "AllowableUnits", AllowableUnits);
    AllowableUnitMaximums = ini.Get_Integer_List("Basic", "AllowableUnitMaximums", AllowableUnitMaximums);
    unknown_222a = ini.Get_Bool("Basic", "TiberiumGrowthEnabled", unknown_222a);
    unknown_222b = ini.Get_Bool("Basic", "VeinGrowthEnabled", unknown_222b);
    unknown_222c = ini.Get_Bool("Basic", "IceGrowthEnabled", unknown_222c);
    TiberiumDeathToVisceroid = ini.Get_Bool("Basic", "TiberiumDeathToVisceroid", TiberiumDeathToVisceroid);
    FreeRadar = ini.Get_Bool("Basic", "FreeRadar", FreeRadar);
    HomeCell = ini.Get_Int("Basic", "HomeCell", HomeCell);
    AltHomeCell = ini.Get_Int("Basic", "AltHomeCell", AltHomeCell);
    ini.Get_Bool("Basic", "CivEvac", false);

    int index;
    for (index = 0; index < AllowableUnits.Count() - AllowableUnitMaximums.Count(); index++) {
        AllowableUnitMaximums.Add(-1);
    }
    for (index = 0; index < AllowableUnitMaximums.Count(); index++) {
        AllowableUnitCounts.Add(0);
    }

    Read_Variables(ini);
    Service_Game_IO_00481fb0();

    ParTimeEasy = ini.Get_Time("Ranking", "ParTimeEasy", ParTimeEasy);
    ParTimeMedium = ini.Get_Time("Ranking", "ParTimeMedium", ParTimeMedium);
    ParTimeHard = ini.Get_Time("Ranking", "ParTimeHard", ParTimeHard);
    ini.Get_String("Ranking", "UnderParTitle", "GUI:NoUnderParTitle", UnderParTitle, sizeof(UnderParTitle));
    ini.Get_String("Ranking", "UnderParMessage", "GUI:NoUnderParMessage", UnderParMessage, sizeof(UnderParMessage));
    ini.Get_String("Ranking", "OverParTitle", "GUI:NoOverParTitle", OverParTitle, sizeof(OverParTitle));
    ini.Get_String("Ranking", "OverParMessage", "GUI:NoOverParMessage", OverParMessage, sizeof(OverParMessage));

    unknown_22b0 = unknown_22ac = unknown_22a8 = ini.Get_Double("Lighting", "Ambient", unknown_22a8 * 0.01) * 100.0;
    AmbientRed = ini.Get_Double("Lighting", "Red", AmbientRed * 0.01) * 100.0;
    AmbientGreen = ini.Get_Double("Lighting", "Green", AmbientGreen * 0.01) * 100.0;
    AmbientBlue = ini.Get_Double("Lighting", "Blue", AmbientBlue * 0.01) * 100.0;
    AmbientGround = ini.Get_Double("Lighting", "Ground", AmbientGround / 1000) * 1000.0;
    AmbientLevel = ini.Get_Double("Lighting", "Level", AmbientLevel / 1000) * 1000.0;
    IonAmbient = ini.Get_Double("Lighting", "IonAmbient", unknown_22a8 * 0.01) * 100.0;
    IonRed = ini.Get_Double("Lighting", "IonRed", AmbientRed * 0.01) * 100.0;
    IonGreen = ini.Get_Double("Lighting", "IonGreen", AmbientGreen * 0.01) * 100.0;
    IonBlue = ini.Get_Double("Lighting", "IonBlue", AmbientBlue * 0.01) * 100.0;
    IonGround = ini.Get_Double("Lighting", "IonGround", AmbientGround / 1000) * 1000.0;
    IonLevel = ini.Get_Double("Lighting", "IonLevel", AmbientLevel / 1000) * 1000.0;
    NukeAmbientChangeRate = ini.Get_Double("Lighting", "NukeAmbientChangeRate", NukeAmbientChangeRate);
    unknown_session_a3d298.Loading_Progress_00672160(55);
    Service_Game_IO_00481fb0();

    if (unknown_game_mode_a3d298 == 0) {
        char player[20];
        ini.Get_String("Basic", "Player", unknown_string_83c55c, player, sizeof(player));
        int house = HouseClass::Find_Index(player);
        if (house == -1) {
            house = 0;
        }
        unknown_player_a35db4 = Houses[house];
        unknown_11fc = unknown_player_a35db4->Type->House;
    } else {
        Assign_Houses_0065fbb0();
    }
    unknown_player_a35db4->unknown_134 = true;
    unknown_player_a35db4->unknown_135 = true;
    unknown_player_a35db4->unknown_55e4 = 0;
    unknown_session_a3d298.Loading_Progress_00672160(58);
    Service_Game_IO_00481fb0();
    if (unknown_flag_a40d13) {
        Reset_Light_Converts_00529720();
    }
    unknown_session_a3d298.Loading_Progress_00672160(60);
    Service_Game_IO_00481fb0();
    return true;
}
