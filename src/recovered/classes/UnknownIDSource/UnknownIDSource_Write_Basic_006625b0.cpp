// bool UnknownIDSource::Write_Basic(CCINIClass &ini, bool skip_player) (0x006625B0)
// Writes the scenario's [Basic] settings (the player, the movies, the carried
// money and the home cells only when not skip_player), its local variables
// ([VariableNames], "name,value" by index), the par times ([Ranking]) and the
// lighting levels ([Lighting], stored in hundredths or thousandths); always
// true. UnknownIDSource is the scenario object (ScenarioClass in TS).
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_03GOGG@Red?$AA@=007d61f8
// @ref ??_C@_03JKEC@Win?$AA@=007f2628
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4
// @ref ??_C@_04KPAE@Blue?$AA@=007d649c
// @ref ??_C@_04NLLM@Lose?$AA@=007f2620
// @ref ??_C@_05DKMC@Green?$AA@=007d61fc
// @ref ??_C@_05JGCF@Brief?$AA@=007f1e58
// @ref ??_C@_05LOBO@?$CFs?0?$CFd?$AA@=007f2390
// @ref ??_C@_05MDNJ@Intro?$AA@=007d9d98
// @ref ??_C@_05PDLI@Theme?$AA@=007d9d6c
// @ref ??_C@_05PGGH@Level?$AA@=007d1374
// @ref ??_C@_06BMKI@UIName?$AA@=007ce29c
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
// @ref ??_C@_08GNBJ@InitTime?$AA@=007f21dc
// @ref ??_C@_08KKNJ@Briefing?$AA@=007ee580
// @ref ??_C@_08NLPB@Official?$AA@=007f21d0
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
// @ref ??_C@_0BG@FMEK@AllowableUnitMaximums?$AA@=007f2500
// @ref ??_C@_0BG@HKNP@TiberiumGrowthEnabled?$AA@=007f24e8
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
// @ref ?Put_Unicode@INIClass@@QAE_NPBD0PBG@Z=0050ecf0
// @ref ?unknown_basic_section_7a9204@@3PBDB=007a9204
// @ref ?unknown_variable_names_section_7a9200@@3PBDB=007a9200
// @ref __real@8@3ff583126e978d4fe000=0079c528
#include "shared/id_source.hpp"
#include "shared/unknown_loadout.hpp"
#include "shared/special.hpp"
#include "shared/ccini_class.hpp"
// The unit's header statics (0x00663DF0-0x00663FD1) come from these two.
#include "shared/shape_file.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/house.hpp"
#include "shared/win32_api.hpp"

bool UnknownIDSource::Write_Basic(CCINIClass &ini, bool skip_player)
{
    ini.Clear(unknown_basic_section_7a9204);
    ini.Clear(unknown_basic_section_7a9204, "CivEvac");
    if (strlen(unknown_id_source_a3d290->Briefing) != 0) {
        ini.Put_String(unknown_basic_section_7a9204, "Briefing", unknown_id_source_a3d290->Briefing);
    }
    if (strlen(unknown_id_source_a3d290->UIName) != 0) {
        ini.Put_String(unknown_basic_section_7a9204, "UIName", unknown_id_source_a3d290->UIName);
    }
    Special().Write_INI(ini);
    ini.Put_String(unknown_basic_section_7a9204, "NextScenario", NextScenario);
    ini.Put_String(unknown_basic_section_7a9204, "AltNextScenario", AltNextScenario);
    ini.Put_Unicode(unknown_basic_section_7a9204, "Name", Name);
    ini.Put_Int(unknown_basic_section_7a9204, "NewINIFormat", 4);
    ini.Put_Int(unknown_basic_section_7a9204, "CarryOverCap", unknown_1208 / 100);
    ini.Put_Bool(unknown_basic_section_7a9204, "EndOfGame", EndOfGame);
    ini.Put_Bool(unknown_basic_section_7a9204, "SkipScore", SkipScore);
    ini.Put_Bool(unknown_basic_section_7a9204, "OneTimeOnly", OneTimeOnly);
    ini.Put_Bool(unknown_basic_section_7a9204, "SkipMapSelect", SkipMapSelect);
    ini.Put_Bool(unknown_basic_section_7a9204, "Official", true);
    ini.Put_Bool(unknown_basic_section_7a9204, "IgnoreGlobalAITriggers", unknown_2238);
    ini.Put_Bool(unknown_basic_section_7a9204, "TruckCrate", TruckCrate);
    ini.Put_Bool(unknown_basic_section_7a9204, "TrainCrate", unknown_2229);
    ini.Put_Int(unknown_basic_section_7a9204, "Percent", Percent);
    ini.Put_Techno_List(unknown_basic_section_7a9204, "AllowableUnits", Loadout_Types_2254());
    ini.Put_Integer_List(unknown_basic_section_7a9204, "AllowableUnitMaximums", Loadout_Limits_2270());
    ini.Put_ThemeType(unknown_basic_section_7a9204, "Theme", Theme);

    if (!skip_player) {
        char player[32];
        strcpy(player, unknown_player_a35db4->IniName);
        ini.Put_String(unknown_basic_section_7a9204, "Player", player);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "Intro", IntroMovie);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "Brief", BriefMovie);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "Win", WinMovie);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "Lose", LoseMovie);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "Action", ActionMovie);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "PostScore", PostScoreMovie);
        ini.Put_Listed_Name(unknown_basic_section_7a9204, "PreMapSelect", PreMapSelectMovie);
        ini.Put_Double(unknown_basic_section_7a9204, "CarryOverMoney", CarryOverMoney);
        ini.Put_Bool(unknown_basic_section_7a9204, "TimerInherit", unknown_2231);
        ini.Put_Bool(unknown_basic_section_7a9204, "FillSilos", FillSilos);
        ini.Put_Int(unknown_basic_section_7a9204, "StartingDropships", StartingDropships);
        ini.Put_Int(unknown_basic_section_7a9204, "HomeCell", HomeCell);
        ini.Put_Int(unknown_basic_section_7a9204, "AltHomeCell", AltHomeCell);
    }
    ini.Put_Int(unknown_basic_section_7a9204, "MultiplayerOnly", MultiplayerOnly);
    ini.Put_Bool(unknown_basic_section_7a9204, "TiberiumGrowthEnabled", unknown_222a);
    ini.Put_Bool(unknown_basic_section_7a9204, "VeinGrowthEnabled", unknown_222b);
    ini.Put_Bool(unknown_basic_section_7a9204, "IceGrowthEnabled", unknown_222c);
    ini.Put_Bool(unknown_basic_section_7a9204, "TiberiumDeathToVisceroid", TiberiumDeathToVisceroid);
    ini.Put_Bool(unknown_basic_section_7a9204, "FreeRadar", FreeRadar);
    ini.Put_Int(unknown_basic_section_7a9204, "InitTime", InitTime);

    ini.Clear(unknown_variable_names_section_7a9200);
    for (int index = 0; index < 50; index++) {
        UnknownScenarioVariable_004B5AB0 &variable = LocalVariables[index];
        if (variable.unknown_00[0] != 0) {
            char entry[12];
            char value[128];
            wsprintfA(entry, "%d", index);
            wsprintfA(value, "%s,%d", variable.unknown_00, variable.Value != 0);
            ini.Put_String(unknown_variable_names_section_7a9200, entry, value);
        }
    }

    ini.Put_Time("Ranking", "ParTimeEasy", ParTimeEasy);
    ini.Put_Time("Ranking", "ParTimeMedium", ParTimeMedium);
    ini.Put_Time("Ranking", "ParTimeHard", ParTimeHard);
    ini.Put_String("Ranking", "UnderParTitle", UnderParTitle);
    ini.Put_String("Ranking", "UnderParMessage", UnderParMessage);
    ini.Put_String("Ranking", "OverParTitle", OverParTitle);
    ini.Put_String("Ranking", "OverParMessage", OverParMessage);

    ini.Clear("Lighting");
    double ambient = unknown_22a8 * 0.01;
    ini.Put_Double("Lighting", "Ambient", ambient);
    double red = AmbientRed * 0.01;
    ini.Put_Double("Lighting", "Red", red);
    double green = AmbientGreen * 0.01;
    ini.Put_Double("Lighting", "Green", green);
    double blue = AmbientBlue * 0.01;
    ini.Put_Double("Lighting", "Blue", blue);
    double ground = AmbientGround * 0.001;
    ini.Put_Double("Lighting", "Ground", ground);
    double level = AmbientLevel * 0.001;
    ini.Put_Double("Lighting", "Level", level);
    double ionambient = IonAmbient * 0.01;
    ini.Put_Double("Lighting", "IonAmbient", ionambient);
    double ionred = IonRed * 0.01;
    ini.Put_Double("Lighting", "IonRed", ionred);
    double iongreen = IonGreen * 0.01;
    ini.Put_Double("Lighting", "IonGreen", iongreen);
    double ionblue = IonBlue * 0.01;
    ini.Put_Double("Lighting", "IonBlue", ionblue);
    double ionground = IonGround * 0.001;
    ini.Put_Double("Lighting", "IonGround", ionground);
    double ionlevel = IonLevel * 0.001;
    ini.Put_Double("Lighting", "IonLevel", ionlevel);
    return true;
}
