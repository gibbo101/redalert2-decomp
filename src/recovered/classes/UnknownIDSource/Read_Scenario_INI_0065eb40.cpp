// bool __fastcall Read_Scenario_INI(CCINIClass &ini, bool official) (0x0065EB40)
// Reads a scenario: the difficulty and fog of war from the session, the
// campaign's MISSION.INI texts (name, briefing, loading screen) and the
// scenario's own <name>.INI rules addition in a normal game, the theater,
// the rules sections, the global variables, the houses and [Basic]
// (Read_Basic), then every object list (teams, scripts, task forces,
// triggers, tags, AI triggers, the map, terrain, overlays, units, aircraft,
// infantry, buildings, smudges). Reports the loading progress along the
// way; false when the player side or [Basic] cannot be set up.
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0Tactical@@QAE@XZ=006a24b0
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_C@_03DIFO@Map?$AA@=007d5c9c
// @ref ??_C@_04CLNG@?4INI?$AA@=007f21c8
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4
// @ref ??_C@_05FGDF@Basic?$AA@=007e1a50
// @ref ??_C@_06BMKI@UIName?$AA@=007ce29c
// @ref ??_C@_06HJOA@Player?$AA@=007e1a58
// @ref ??_C@_07OHHF@Theater?$AA@=007cf004
// @ref ??_C@_08GNBJ@InitTime?$AA@=007f21dc
// @ref ??_C@_08KKNJ@Briefing?$AA@=007ee580
// @ref ??_C@_08NLPB@Official?$AA@=007f21d0
// @ref ??_C@_09INJI@Americans?$AA@=007f213c
// @ref ??_C@_0BE@DADK@D?3?2Ra2?2Scenario?4CPP?$AA@=007f1df0
// @ref ??_C@_0BH@KFKP@Clearing?5old?5scenario?6?$AA@=007f21e8
// @ref ??_C@_0L@HNHO@TMCJ4F?4INI?$AA@=007f2130
// @ref ??_C@_0M@CGFN@MISSION?4INI?$AA@=007ee58c
// @ref ??_C@_0O@DJPF@LSLoadMessage?$AA@=007f21b8
// @ref ??_C@_0O@EALI@LS640BkgdName?$AA@=007f2158
// @ref ??_C@_0O@FEOP@LS800BkgdName?$AA@=007f2148
// @ref ??_C@_0O@JLPK@VariableNames?$AA@=007f1ddc
// @ref ??_C@_0P@DAIG@LS640BriefLocY?$AA@=007f2188
// @ref ??_C@_0P@DDAF@LS800BriefLocX?$AA@=007f2178
// @ref ??_C@_0P@EHON@LSLoadBriefing?$AA@=007f21a8
// @ref ??_C@_0P@JJJC@LS800BriefLocY?$AA@=007f2168
// @ref ??_C@_0P@JKBB@LS640BriefLocX?$AA@=007f2198
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ?Clear_Scenario_0065d370@@YAXXZ=0065d370
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ?Find_Entry@INIClass@@QBEPAUINIEntry@1@PBD0@Z=0050cca0
// @ref ?Find_Section@INIClass@@QBEPAUINISection@1@PBD@Z=0050c9b0
// @ref ?Init_Theater_00519e70@@YIXH@Z=00519e70
// @ref ?Process@RulesClass@@QAEXAAVCCINIClass@@@Z=006433a0
// @ref ?Read_INI@BuildingClass@@SIXAAVCCINIClass@@@Z=0044ab80
// @ref ?Read_INI@TerrainClass@@SIXAAVCCINIClass@@@Z=006e4260
// @ref ?Read_INI@UnitClass@@SIXAAVCCINIClass@@@Z=00706ae0
// @ref ?Read_INI_0049CFD0@DisplayClass@@QAEXAAVCCINIClass@@@Z=0049cfd0
// @ref ?Reset@SwizzleManagerClass@@UAGJXZ=0069fb10
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Unknown_0042E1A0@Unknown84E8D0@@QAEXXZ=0042e1a0
// @ref ?Unknown_0051a330@@YI_NH@Z=0051a330
// @ref ?Unknown_00535910@@YAPAUUnknown535910@@XZ=00535910
// @ref ?Unknown_00535BF0@Unknown535910@@QAEXXZ=00535bf0
// @ref ?Unknown_0065e8c0@@YIX_N@Z=0065e8c0
// @ref ?Unknown_0068B410@SpecialClass@@QAEXXZ=0068b410
// @ref ?Unknown_006c0220@@YIXXZ=006c0220
// @ref ?Unknown_006e9520@@YIXXZ=006e9520
// @ref ?Unknown_006e9fe0@@YAXXZ=006e9fe0
// @ref ?Unknown_006ecf10@@YAXXZ=006ecf10
// @ref ?Read_INI@TubeClass@@SIXAAVCCINIClass@@@Z=006ef5c0
// @ref ?unknown_7df630@@3_NA=007df630
// @ref ?unknown_a40770@@3HA=00a40770
// @ref ?unknown_a40d39@@3_NA=00a40d39
// @ref ?unknown_difficulty_a40b1c@@3HA=00a40b1c
// @ref ?unknown_func_45ebd0@BuildingTypeClass@@SIXXZ=0045ebd0
// @ref ?unknown_ini_839860@@3VCCINIClass@@A=00839860
// @ref ?unknown_session_a3d2c0@@3_NA=00a3d2c0
// @ref ?unknown_session_difficulty_a3d2d8@@3HA=00a3d2d8
// @ref ?unknown_session_fog_a3d33f@@3_NA=00a3d33f
// @ref ?unknown_special_a40920@@3VSpecialClass@@A=00a40920
// @ref __splitpath=00784873
#include "shared/id_source.hpp"
#include "shared/unknown_loadout.hpp"
#include "shared/special.hpp"
#include "shared/ccini_class.hpp"
#include "shared/shape_file.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/house.hpp"
#include "shared/win32_api.hpp"
#include "shared/session_state.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/debug_printf.hpp"
#include "shared/string_table.hpp"
#include "shared/rules.hpp"
#include "shared/campaign.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/tactical.hpp"
#include "shared/team_type.hpp"
#include "shared/script.hpp"
#include "shared/task_force.hpp"
#include "shared/trigger_type.hpp"
#include "shared/tag_type.hpp"
#include "shared/tube.hpp"
#include "shared/ai_trigger_type.hpp"
#include "shared/map_view.hpp"
#include "shared/terrain.hpp"
#include "shared/overlay.hpp"
#include "shared/veinhole.hpp"
#include "shared/smudge.hpp"
#include "shared/abstract.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_class.hpp"

// Westwood-style macro: each operand is evaluated where it appears.
#define Min(a, b) ((a) < (b) ? (a) : (b))


bool __fastcall Read_Scenario_INI(CCINIClass &ini, bool official)
{
    char buffer[32];
    unknown_a40774++;
    Debug_Printf("Clearing old scenario\n");
    Clear_Scenario_0065d370();
    if (unknown_game_mode_a3d298 == 0) {
        unknown_id_source_a3d290->Difficulty = unknown_difficulty_a40b1c;
        unknown_id_source_a3d290->unknown_610 = 2 - unknown_difficulty_a40b1c;
        unknown_id_source_a3d290->Special().FogOfWar = false;
        unknown_special_a40920.FogOfWar = false;
    } else {
        unknown_id_source_a3d290->Difficulty = unknown_session_difficulty_a3d2d8;
        unknown_id_source_a3d290->unknown_610 = 2 - unknown_id_source_a3d290->Difficulty;
        unknown_id_source_a3d290->Special().FogOfWar = unknown_session_fog_a3d33f;
        unknown_special_a40920.FogOfWar = unknown_session_fog_a3d33f;
    }
    unknown_id_source_a3d290->InitTime = ini.Get_Int("Basic", "InitTime", 10000);
    ini.Get_Bool("Basic", "Official", false);

    CCINIClass mission;
    CCFileClass file;
    if (unknown_game_mode_a3d298 == 0) {
        _splitpath(unknown_id_source_a3d290->FileName, 0, 0, buffer, 0);
        strcat(buffer, ".INI");
        file.Set_Name(buffer);
        if (file.Is_Available(0)) {
            mission.Load(file, false, false);
            Rules->Addition(mission);
        }
        file.Close();
        file.Set_Name("MISSION.INI");
        if (file.Is_Available(0)) {
            mission.Load(file, false, false);
            UnknownIDSource *scen = unknown_id_source_a3d290;
            unknown_id_source_a3d290->Name[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "Name")) {
                mission.Get_Unicode(unknown_id_source_a3d290->FileName, "Name", unknown_empty_wide_839d4c, unknown_id_source_a3d290->Name, 45);
            }
            unknown_id_source_a3d290->BriefingText[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "Briefing")) {
                mission.Get_String(unknown_id_source_a3d290->FileName, "Briefing", unknown_string_83c55c, unknown_id_source_a3d290->Briefing, 32);
                if (strlen(unknown_id_source_a3d290->Briefing) != 0) {
                    wcsncpy(unknown_id_source_a3d290->BriefingText, StringTable::Load_String(unknown_id_source_a3d290->Briefing, 0, "D:\\Ra2\\Scenario.CPP", 3180), 0x400);
                    unknown_id_source_a3d290->BriefingText[0x3FF] = 0;
                }
            }
            unknown_id_source_a3d290->UIName[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "UIName")) {
                mission.Get_String(unknown_id_source_a3d290->FileName, "UIName", unknown_string_83c55c, unknown_id_source_a3d290->UIName, 32);
                if (strlen(unknown_id_source_a3d290->UIName) != 0) {
                    wcsncpy(unknown_id_source_a3d290->Name, StringTable::Load_String(unknown_id_source_a3d290->UIName, 0, "D:\\Ra2\\Scenario.CPP", 3192), 45);
                    unknown_id_source_a3d290->Name[44] = 0;
                }
            }
            unknown_id_source_a3d290->LSLoadMessage[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LSLoadMessage")) {
                mission.Get_String(unknown_id_source_a3d290->FileName, "LSLoadMessage", unknown_string_83c55c, unknown_id_source_a3d290->LSLoadMessage, 31);
            }
            unknown_id_source_a3d290->LSLoadBriefing[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LSLoadBriefing")) {
                mission.Get_String(unknown_id_source_a3d290->FileName, "LSLoadBriefing", unknown_string_83c55c, unknown_id_source_a3d290->LSLoadBriefing, 31);
            }
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LS640BriefLocX")) {
                unknown_id_source_a3d290->LS640BriefLocX = mission.Get_Int(unknown_id_source_a3d290->FileName, "LS640BriefLocX", unknown_id_source_a3d290->LS640BriefLocX);
            }
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LS640BriefLocY")) {
                unknown_id_source_a3d290->LS640BriefLocY = mission.Get_Int(unknown_id_source_a3d290->FileName, "LS640BriefLocY", unknown_id_source_a3d290->LS640BriefLocY);
            }
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LS800BriefLocX")) {
                unknown_id_source_a3d290->LS800BriefLocX = mission.Get_Int(unknown_id_source_a3d290->FileName, "LS800BriefLocX", unknown_id_source_a3d290->LS800BriefLocX);
            }
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LS800BriefLocY")) {
                unknown_id_source_a3d290->LS800BriefLocY = mission.Get_Int(unknown_id_source_a3d290->FileName, "LS800BriefLocY", unknown_id_source_a3d290->LS800BriefLocY);
            }
            unknown_id_source_a3d290->LS640BkgdName[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LS640BkgdName")) {
                mission.Get_String(unknown_id_source_a3d290->FileName, "LS640BkgdName", unknown_string_83c55c, unknown_id_source_a3d290->LS640BkgdName, 64);
            }
            unknown_id_source_a3d290->LS800BkgdName[0] = 0;
            if (mission.Is_Present(unknown_id_source_a3d290->FileName, "LS800BkgdName")) {
                mission.Get_String(unknown_id_source_a3d290->FileName, "LS800BkgdName", unknown_string_83c55c, unknown_id_source_a3d290->LS800BkgdName, 64);
            }
        }
    }

    Unknown_00535910()->Unknown_00535BF0();
    unknown_session_a3d298.Loading_Progress_00672160(3);
    SwizzleManager.Reset();
    delete unknown_tactical_83996c;
    unknown_tactical_83996c = new Tactical;
    unknown_tactical_83996c->Unknown_006A65A0(unknown_rect_839630);
    unknown_id_source_a3d290->Theater = ini.Get_TheaterType("Map", "Theater", (TheaterType)0);
    Init_Theater_00519e70(unknown_id_source_a3d290->Theater);
    unknown_session_a3d298.Loading_Progress_00672160(30);
    Rules->Advanced_Command_Bar(unknown_ini_839860, unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5);
    unknown_session_a3d298.Loading_Progress_00672160(31);
    Rules->Process(*unknown_ini_8396d0);
    unknown_session_a3d298.Loading_Progress_00672160(35);
    Service_Game_IO_00481fb0();

    UnknownIDSource *scenario = unknown_id_source_a3d290;
    CCINIClass &rules = *unknown_ini_8396d0;
    int count = Min(rules.Entry_Count("VariableNames"), 50);
    for (int index = 0; index < count; index++) {
        char const *entry = rules.Get_Entry("VariableNames", index);
        int slot = atoi(entry);
        rules.Get_String("VariableNames", entry, 0, scenario->Variables[slot].unknown_00, 40);
    }
    Service_Game_IO_00481fb0();
    Rules->Addition(ini);
    unknown_session_a3d298.Loading_Progress_00672160(45);

    unknown_a40770 = 0;
    scenario = unknown_id_source_a3d290;
    int side = 0;
    if (unknown_game_mode_a3d298 == 0) {
        if (scenario->unknown_224c != -1) {
            side = Campaigns[scenario->unknown_224c]->unknown_98;
        }
    } else {
        int country = unknown_players_a3fa7c[0]->unknown_4b;
        if (country == -3) {
            country = 0;
        }
        side = HouseTypes[country]->Side;
    }
    bool allied = side == 0;
    if (unknown_game_mode_a3d298 == 0) {
        HouseClass::Read_Scenario_INI(ini);
        ini.Get_String("Basic", "Player", "Americans", buffer, sizeof(buffer));
        int house = HouseClass::Find_Index(buffer);
        if (house != -1 && house <= Houses.Count()) {
            allied = Houses[house]->Type->Side == 0;
        } else {
            allied = false;
        }
        unknown_id_source_a3d290->unknown_2239 = allied;
        if (!Unknown_0051a330(!allied)) {
            unknown_a40774--;
            return false;
        }
    } else {
        scenario->unknown_2239 = allied;
        if (!Unknown_0051a330(!allied)) {
            unknown_a40774--;
            return false;
        }
    }
    unknown_session_a3d298.Loading_Progress_00672160(50);
    if (!unknown_id_source_a3d290->Read_Basic(ini)) {
        unknown_a40774--;
        return false;
    }
    unknown_session_a3d298.Loading_Progress_00672160(58);
    if (unknown_game_mode_a3d298 == 0) {
        char player[32];
        ini.Get_String("Basic", "Player", "Americans", player, sizeof(player));
        int house = HouseClass::Find_Index(player);
        if (house != -1 && house <= Houses.Count()) {
            allied = Houses[house]->Type->Side == 0;
        } else {
            allied = false;
        }
        if (!Unknown_0051a330(!allied)) {
            unknown_a40774--;
            return false;
        }
        unknown_id_source_a3d290->unknown_2239 = allied;
    } else {
        unknown_id_source_a3d290->unknown_2239 = allied;
        if (unknown_session_a3d29c) {
            unknown_session_a3d29c->unknown_slot26();
        }
    }
    if (unknown_game_mode_a3d298 != 0 && !unknown_session_a3d2c0) {
        unknown_special_a40920.DestroyableBridges = false;
    }
    unknown_special_a40920.Unknown_0068B410();
    Service_Game_IO_00481fb0();

    TeamTypeClass::Read_Scenario_INI(unknown_ini_8397a0, 1);
    TeamTypeClass::Read_Scenario_INI(ini, 0);
    ScriptTypeClass::Read_Scenario_INI(unknown_ini_8397a0, 1);
    ScriptTypeClass::Read_Scenario_INI(ini, 0);
    TaskForceClass::Read_Scenario_INI(unknown_ini_8397a0, 1);
    TaskForceClass::Read_Scenario_INI(ini, 0);
    TriggerTypeClass::Read_Scenario_INI(ini);
    TagTypeClass::Read_Scenario_INI(ini);
    AITriggerTypeClass::Read_Scenario_INI(unknown_ini_8397a0, 1);
    AITriggerTypeClass::Read_Scenario_INI(ini, 0);
    Unknown_006c0220();
    unknown_session_a3d298.Loading_Progress_00672160(60);
    Map.Read_INI_0049CFD0(ini);
    Service_Game_IO_00481fb0();
    TubeClass::Read_INI(ini);
    BuildingTypeClass::unknown_func_45ebd0();
    Map.Flag_To_Redraw(2);
    unknown_session_a3d298.Loading_Progress_00672160(70);
    Service_Game_IO_00481fb0();
    OverlayClass::Read_INI(ini);
    Service_Game_IO_00481fb0();
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell; cell = Map.Unknown_0055A490()) {
        cell->Unknown_00472540(-1);
    }
    OverlayClass::unknown_func_5dc180();
    TerrainClass::Read_INI(ini);
    Service_Game_IO_00481fb0();
    VeinholeMonsterClass::unknown_func_711280(true);
    Unknown_006e9fe0();
    Unknown_006e9520();
    unknown_session_a3d298.Loading_Progress_00672160(72);
    Map.Unknown_00630A00();
    UnitClass::Read_INI(ini);
    Service_Game_IO_00481fb0();
    unknown_session_a3d298.Loading_Progress_00672160(74);
    AircraftClass::Read_INI_0041A840(ini);
    Service_Game_IO_00481fb0();
    InfantryClass::Read_INI(ini);
    Service_Game_IO_00481fb0();
    unknown_session_a3d298.Loading_Progress_00672160(76);
    unknown_7df630 = false;
    BuildingClass::Read_INI(ini);
    Service_Game_IO_00481fb0();
    unknown_session_a3d298.Loading_Progress_00672160(78);
    unknown_7df630 = true;
    Service_Game_IO_00481fb0();
    SmudgeClass::Read_INI(ini);
    Service_Game_IO_00481fb0();
    if (unknown_game_mode_a3d298 == 5 && unknown_a40d39) {
        file.Close();
        file.Set_Name("TMCJ4F.INI");
        if (file.Is_Available(0) == true) {
            mission.Load(file, false, false);
            Rules->Addition(mission);
        }
    }
    unknown_session_a3d298.Loading_Progress_00672160(82);
    Service_Game_IO_00481fb0();
    Map.Unknown_0054B2E0();
    unknown_session_a3d298.Loading_Progress_00672160(86);
    Service_Game_IO_00481fb0();
    unknown_object_84e8d0.Unknown_0042E1A0();
    unknown_session_a3d298.Loading_Progress_00672160(90);
    Service_Game_IO_00481fb0();
    if (unknown_game_mode_a3d298 != 0 && !official) {
        Unknown_0065e8c0(ini.Get_Bool("Basic", "Official", false));
    }
    Service_Game_IO_00481fb0();
    SwizzleManager.Reset();
    unknown_session_a3d298.Loading_Progress_00672160(96);
    Service_Game_IO_00481fb0();
    Unknown_006ecf10();
    if (unknown_game_mode_a3d298 != 0) {
        unknown_id_source_a3d290->Special() = unknown_special_a40920;
    }
    unknown_a40774--;
    int init = unknown_a40774;
    unknown_a40774 = 0;
    BuildingClass::unknown_44df40();
    unknown_a40774 = init;
    unknown_session_a3d298.Loading_Progress_00672160(98);
    Service_Game_IO_00481fb0();
    Map.Clear_Redraw_Cells();
    if (unknown_id_source_a3d290->unknown_000 & 0x1000) {
        Map.Unknown_005685F0();
    }
    RadarEventClass_unknown_delete_all_63c640();
    Map.Unknown_00634030();
    return true;
}
