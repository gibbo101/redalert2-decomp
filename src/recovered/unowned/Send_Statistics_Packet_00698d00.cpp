// Send_Statistics_Packet (Stats.CPP, 0x00698D00; keeps its current symbol): builds the game results packet and sends
// it through the ladder client. `arg` selects the WDT host and SKU.
#define RA2_STATS_UNIT
#include "shared/win32_api.hpp"
#include "shared/directdraw.hpp"
#include "shared/dsurface.hpp"
#include "shared/queue.hpp"
#include "shared/house.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/aircraft.hpp"
#include "shared/house_type.hpp"
#include "shared/packet.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/session_state.hpp"
#include "shared/unit_tracker.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_sink.hpp"

extern "C" __declspec(dllimport) void __stdcall GlobalMemoryStatus(MEMORYSTATUS *status);
extern "C" unsigned long __stdcall htonl(unsigned long value);
extern unsigned int unknown_b2ab84;
extern int unknown_b2668c;
extern int unknown_b2a7fc;
extern int unknown_b2a7ec;
extern int unknown_b2a630;
extern int unknown_b2aaf8;
extern char unknown_b2a808[];
extern char unknown_b2a6d8[];
extern long unknown_game_start_time_b2a638;
extern char unknown_cpu_family_8015a3;
extern int unknown_a40b18;
extern int unknown_session_a3d2a0;
extern bool unknown_flag_a3d8d1;
extern bool unknown_flag_a3d8d2;
extern bool unknown_flag_a417c8;
extern int unknown_elapsed_abd4e0;
extern void *ProgramInstance;
extern "C" __declspec(dllimport) int __stdcall GetFileTime(HANDLE file, FILETIME *created, FILETIME *accessed, FILETIME *written);

#define TRACKER(member) (*(UnitTrackerClass *)&player->member)
#define UNIT_TOTALS(member) TRACKER(member).Get_All_Totals(), unknown_last_used_count_0069a110(TRACKER(member).Get_All_Totals(), TRACKER(member).UnitCount) * 4

int __fastcall unknown_last_used_count_0069a110(int const *slots, int count);

void __fastcall Unknown_00698D00(bool arg)
{
    PacketClass stats;
    unsigned int playercount = 0;
    unsigned int statsid = 0;
    if (unknown_house_a72d28 && unknown_player_a35db4 == unknown_house_a72d28) {
        return;
    }
    HouseClass *player;
    static int packet_size;
    unsigned int i;
    void *packet;
    unsigned int temp;
    static char field_player_handle[5] = { "NAM?" };
    static char field_player_team[5] = { "SID?" };
    static char field_player_t_team[5] = { "TID?" };
    static char field_player_color[5] = { "COL?" };
    static char field_player_country[5] = { "CTY?" };
    static char field_player_credits[5] = { "CRD?" };
    static char field_player_units_left[5] = { "UNL?" };
    static char field_player_infantry_left[5] = { "INL?" };
    static char field_player_planes_left[5] = { "PLL?" };
    static char field_player_buildings_left[5] = { "BLL?" };
    static char field_player_units_bought[5] = { "UNB?" };
    static char field_player_infantry_bought[5] = { "INB?" };
    static char field_player_planes_bought[5] = { "PLB?" };
    static char field_player_buildings_bought[5] = { "BLB?" };
    static char field_player_units_killed[5] = { "UNK?" };
    static char field_player_infantry_killed[5] = { "INK?" };
    static char field_player_planes_killed[5] = { "PLK?" };
    static char field_player_buildings_killed[5] = { "BLK?" };
    static char field_player_buildings_captured[5] = { "BLC?" };
    static char field_player_crates_found[5] = { "CRA?" };
    static char field_player_harvested[5] = { "HRV?" };
    static char field_player_completion[5] = { "CMP?" };
    static char field_player_ip[5] = { "IPA?" };
    static char field_player_clan[5] = { "CID?" };
    static char field_player_lost_connection[5] = { "LCN?" };

    Debug_Printf("Sending game results.  SawCompletion=%d\n", unknown_flag_a3d8d1);

    stats.Add_Field("IDNO", (unsigned int)unknown_b2a7fc);
    if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2) {
        stats.Add_Field("WDTT", unknown_session_a3d2a0);
        if (arg) {
            stats.Add_Field("GSKU", (unsigned int)unknown_b2ab84);
        } else {
            stats.Add_Field("GSKU", (unsigned int)unknown_b2668c);
        }
    } else {
        stats.Add_Field("GSKU", (unsigned int)unknown_b2ab84);
    }
    stats.Add_Field("TRNY", (unsigned int)unknown_b2a7ec);
    if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2 && arg) {
        unknown_b2a7ec = 0;
    }
    stats.Add_Field("OOSY", (unsigned char)(unknown_flag_a3d8d2 == true));
    stats.Add_Field("FINI", (unsigned char)(unknown_flag_a3d8d1 == true));
    stats.Add_Field("DURA", (unsigned int)unknown_elapsed_abd4e0 / 60);
    stats.Add_Field("CRED", (unsigned int)unknown_session_a3d298.unknown_24);
    stats.Add_Field("SHRT", (unsigned char)(unknown_session_a3d298.unknown_2a != false));
    stats.Add_Field("SUPR", (unsigned char)(unknown_session_a3d298.unknown_2b != false));
    stats.Add_Field("MODE", (unsigned int)unknown_session_a3d298.GameModeIndex);
    stats.Add_Field("BAMR", (unsigned int)(((unknown_session_a3d298.unknown_2c == true) << 1) + (unknown_session_a3d298.unknown_a8 == true)));
    stats.Add_Field("CRAT", (unsigned char)(unknown_session_a3d298.unknown_crates_29 != false));
    stats.Add_Field("AIPL", (unsigned int)unknown_session_a3d298.AICount);
    stats.Add_Field("UNIT", (unsigned int)unknown_session_a3d298.UnitCount);
    stats.Add_Field("SCEN", unknown_session_a3d298.ScenarioFileName_658);
    stats.Add_Field("PNGS", (unsigned int)unknown_b2a630);
    stats.Add_Field("PNGR", (unsigned int)unknown_b2aaf8);

    HouseClass *houses[8];
    for (int h = 0; h < Houses.Count(); h++) {
        HouseClass *ptr = Houses[h];
        if (ptr->unknown_134 && ptr != unknown_house_a72d28) {
            houses[playercount] = ptr;
            playercount++;
        }
    }
    for (i = 0; i < playercount; i++) {
        for (unsigned int j = 0; j < (playercount - i) - 1; j++) {
            HouseClass *ptr1 = houses[j + 1];
            HouseClass *ptr2 = houses[j];
            if (_stricmp(ptr2->IniName, ptr1->IniName) > 0) {
                houses[j] = ptr1;
                houses[j + 1] = ptr2;
            }
        }
    }
    for (i = 1; i < playercount; i++) {
        HouseClass *ptr = houses[i];
        if (_stricmp(ptr->IniName, unknown_b2a808) == 0) {
            HouseClass *tmp = houses[0];
            houses[0] = ptr;
            houses[i] = tmp;
        }
    }
    for (i = 0; i < playercount; i++) {
        HouseClass *ptr = houses[i];
        if (_stricmp(ptr->IniName, unknown_b2a6d8) == 0) {
            statsid = i;
            break;
        }
    }
    stats.Add_Field("PLRS", (unsigned int)playercount);
    stats.Add_Field("SPID", (unsigned int)statsid);

    int completion[8];
    for (i = 0; i < playercount; i++) {
        if (!unknown_flag_a3d8d1) {
            completion[i] = 1 << 3;
        } else {
            HouseClass *hptr = houses[i];
            if (hptr->unknown_150) {
                completion[i] = 1 << 1;
            } else if (hptr->unknown_18f || hptr->unknown_18e) {
                completion[i] = (1 << 9) | (1 << 4);
            } else if (hptr->unknown_13d) {
                completion[i] = 1 << 9;
            } else {
                completion[i] = 1 << 8;
            }
        }
    }
    stats.Add_Field("TIME", (int)unknown_game_start_time_b2a638);
    int divisor = unknown_elapsed_abd4e0 / 60;
    if (divisor != 0) {
        stats.Add_Field("AFPS", (unsigned int)Frame / (unknown_elapsed_abd4e0 / 60));
    } else {
        stats.Add_Field("AFPS", 0);
    }
    stats.Add_Field("PROC", (char)unknown_cpu_family_8015a3);

    MEMORYSTATUS mem_info;
    mem_info.dwLength = sizeof(mem_info);
    GlobalMemoryStatus(&mem_info);
    stats.Add_Field("MEMO", (int)mem_info.dwTotalPhys);

    DDCAPS video_capabilities;
    int video_memory;
    if (DirectDrawObject) {
        video_capabilities.dwSize = sizeof(video_capabilities);
        if (DD_OK == DirectDrawObject->GetCaps(&video_capabilities, 0)) {
            video_memory = video_capabilities.dwVidMemTotal;
            video_memory += 1024 * 1024 - 1;
            video_memory &= 0xfff00000;
            stats.Add_Field("VIDM", (int)video_memory);
        }
    }
    stats.Add_Field("SPED", (char)unknown_a40b18);

    char version[128];
    wsprintfA(version, "V%s", version_object_00a40c88.Internal_Version_Name_00712ed0());
    stats.Add_Field("VERS", (char const *)version);

    char path_to_exe[280];
    FILETIME write_time;
    GetModuleFileNameA(ProgramInstance, path_to_exe, sizeof(path_to_exe));
    RawFileClass file;
    file.Set_Name(path_to_exe);
    file.Open();
    HANDLE handle = file.Get_File_Handle();
    if (handle != INVALID_HANDLE_VALUE) {
        if (GetFileTime(handle, 0, 0, &write_time)) {
            write_time.dwLowDateTime = htonl(write_time.dwLowDateTime);
            write_time.dwHighDateTime = htonl(write_time.dwHighDateTime);
            stats.Add_Field("DATE", (void const *)&write_time, sizeof(write_time));
        }
    }

    for (i = 0; i < playercount; i++) {
        player = houses[i];
        char digit = '0' + (char)i;

        field_player_handle[3] = digit;
        stats.Add_Field(field_player_handle, (char const *)player->IniName);

        temp = player->unknown_148;
        field_player_ip[3] = digit;
        stats.Add_Field(field_player_ip, (unsigned int)temp);

        temp = player->unknown_14c;
        field_player_clan[3] = digit;
        stats.Add_Field(field_player_clan, (unsigned int)temp);

        field_player_team[3] = digit;
        stats.Add_Field(field_player_team, (unsigned int)player->unknown_130);

        field_player_t_team[3] = digit;
        temp = i;
        if (unknown_b2a7ec == 2) {
            temp = player->unknown_14c;
        }
        stats.Add_Field(field_player_t_team, (unsigned int)temp);

        field_player_completion[3] = digit;
        stats.Add_Field(field_player_completion, (unsigned int)completion[i]);

        field_player_lost_connection[3] = digit;
        bool lcn = false;
        if (player->unknown_150 && !player->unknown_18e) {
            lcn = true;
        }
        stats.Add_Field(field_player_lost_connection, (unsigned char)lcn);

        field_player_color[3] = digit;
        stats.Add_Field(field_player_color, (unsigned int)player->ColorSchemeIndex);

        field_player_country[3] = digit;
        stats.Add_Field(field_player_country, (unsigned int)player->Type->House);

        field_player_credits[3] = digit;
        stats.Add_Field(field_player_credits, (int)player->Available_Money());

        field_player_infantry_bought[3] = digit;
        field_player_units_bought[3] = digit;
        field_player_planes_bought[3] = digit;
        field_player_buildings_bought[3] = digit;
        TRACKER(unknown_a70).To_Network_Format();
        TRACKER(unknown_1278).To_Network_Format();
        TRACKER(unknown_268).To_Network_Format();
        TRACKER(unknown_1a80).To_Network_Format();
        stats.Add_Field(field_player_infantry_bought, UNIT_TOTALS(unknown_a70));
        stats.Add_Field(field_player_units_bought, UNIT_TOTALS(unknown_1278));
        stats.Add_Field(field_player_planes_bought, UNIT_TOTALS(unknown_268));
        stats.Add_Field(field_player_buildings_bought, UNIT_TOTALS(unknown_1a80));
        TRACKER(unknown_a70).To_PC_Format();
        TRACKER(unknown_1278).To_PC_Format();
        TRACKER(unknown_268).To_PC_Format();
        TRACKER(unknown_1a80).To_PC_Format();

        TRACKER(unknown_a70).Clear_Unit_Total();
        TRACKER(unknown_268).Clear_Unit_Total();
        TRACKER(unknown_1278).Clear_Unit_Total();
        TRACKER(unknown_1a80).Clear_Unit_Total();

        int index;
        for (index = 0; index < Units.Count(); index++) {
            UnitClass const *unit = Units[index];
            if (player == unit->House) {
                TRACKER(unknown_1278).Increment_Unit_Total(unit->Type->ArrayIndex);
            }
        }
        for (index = 0; index < Infantry.Count(); index++) {
            InfantryClass const *infantry = Infantry[index];
            if (player == infantry->House && !infantry->Type->Civilian) {
                TRACKER(unknown_a70).Increment_Unit_Total(infantry->Type->ArrayIndex);
            }
        }
        for (index = 0; index < Aircraft.Count(); index++) {
            AircraftClass const *aircraft = Aircraft[index];
            if (player == aircraft->House) {
                TRACKER(unknown_268).Increment_Unit_Total(aircraft->Type->ArrayIndex);
            }
        }
        int count = player->Buildings.Count();
        for (index = 0; index < count; index++) {
            BuildingClass const *building = player->Buildings[index];
            TRACKER(unknown_1a80).Increment_Unit_Total(building->Type->ArrayIndex);
        }

        TRACKER(unknown_a70).To_Network_Format();
        TRACKER(unknown_1278).To_Network_Format();
        TRACKER(unknown_268).To_Network_Format();
        TRACKER(unknown_1a80).To_Network_Format();
        field_player_infantry_left[3] = digit;
        field_player_units_left[3] = digit;
        field_player_planes_left[3] = digit;
        field_player_buildings_left[3] = digit;
        stats.Add_Field(field_player_infantry_left, UNIT_TOTALS(unknown_a70));
        stats.Add_Field(field_player_units_left, UNIT_TOTALS(unknown_1278));
        stats.Add_Field(field_player_planes_left, UNIT_TOTALS(unknown_268));
        stats.Add_Field(field_player_buildings_left, UNIT_TOTALS(unknown_1a80));

        TRACKER(unknown_2a90).To_Network_Format();
        TRACKER(unknown_3298).To_Network_Format();
        TRACKER(unknown_2288).To_Network_Format();
        TRACKER(unknown_3aa0).To_Network_Format();
        field_player_infantry_killed[3] = digit;
        field_player_units_killed[3] = digit;
        field_player_planes_killed[3] = digit;
        field_player_buildings_killed[3] = digit;
        stats.Add_Field(field_player_infantry_killed, UNIT_TOTALS(unknown_2a90));
        stats.Add_Field(field_player_units_killed, UNIT_TOTALS(unknown_3298));
        stats.Add_Field(field_player_planes_killed, UNIT_TOTALS(unknown_2288));
        stats.Add_Field(field_player_buildings_killed, UNIT_TOTALS(unknown_3aa0));

        field_player_buildings_captured[3] = digit;
        TRACKER(unknown_42a8).To_Network_Format();
        stats.Add_Field(field_player_buildings_captured, UNIT_TOTALS(unknown_42a8));

        field_player_crates_found[3] = digit;
        TRACKER(unknown_4ab0).To_Network_Format();
        stats.Add_Field(field_player_crates_found, UNIT_TOTALS(unknown_4ab0));

        field_player_harvested[3] = digit;
        stats.Add_Field(field_player_harvested, (unsigned int)player->unknown_220);
    }

    packet = stats.Create_Comms_Packet(packet_size);
    if (unknown_ladder_client_a72d00) {
        if (arg) {
            unknown_ladder_client_a72d00->Request_Gameres_Send(unknown_game_address_b2ab00, unknown_game_port_b28dd4, (unsigned char *)packet, packet_size);
        } else {
            unknown_ladder_client_a72d00->Request_Gameres_Send(unknown_game_address_b2a758, unknown_game_port_b28ffc, (unsigned char *)packet, packet_size);
        }
    }
    delete[] packet;
    unknown_flag_a417c8 = true;
}
// @ref ??_C@_03HAAM@V?$CFs?$AA@=007f61b8
// @ref ??_C@_04CBHN@CRAT?$AA@=007f6214
// @ref ??_C@_04CDKL@SPED?$AA@=007f61bc
// @ref ??_C@_04CFBP@TIME?$AA@=007f61dc
// @ref ??_C@_04CGLJ@OOSY?$AA@=007f6254
// @ref ??_C@_04CJNM@DATE?$AA@=007f61a8
// @ref ??_C@_04CLAP@AFPS?$AA@=007f61d4
// @ref ??_C@_04DAHF@MODE?$AA@=007f6224
// @ref ??_C@_04DAPI@SHRT?$AA@=007f6234
// @ref ??_C@_04ECLB@PLRS?$AA@=007f61ec
// @ref ??_C@_04EJEM@SUPR?$AA@=007f622c
// @ref ??_C@_04FKCE@IDNO?$AA@=007f6274
// @ref ??_C@_04FPPO@VERS?$AA@=007f61b0
// @ref ??_C@_04GKKC@PNGR?$AA@=007f61f4
// @ref ??_C@_04JIPN@VIDM?$AA@=007f61c4
// @ref ??_C@_04JNEP@DURA?$AA@=007f6244
// @ref ??_C@_04KGIF@MEMO?$AA@=007f61cc
// @ref ??_C@_04KKA@WDTT?$AA@=007f626c
// @ref ??_C@_04KNPG@AIPL?$AA@=007f620c
// @ref ??_C@_04MADF@PNGS?$AA@=007f61fc
// @ref ??_C@_04MDPC@BAMR?$AA@=007f621c
// @ref ??_C@_04MMFF@SPID?$AA@=007f61e4
// @ref ??_C@_04NCKH@CRED?$AA@=007f623c
// @ref ??_C@_04NELF@GSKU?$AA@=007f6264
// @ref ??_C@_04OJA@TRNY?$AA@=007f625c
// @ref ??_C@_04PFGM@SCEN?$AA@=007f6204
// @ref ??_C@_04PPIB@FINI?$AA@=007f624c
// @ref ??_C@_0CJ@HGG@Sending?5game?5results?4?5?5SawComple@=007f627c
// @ref _?field_player_buildings_bought@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6148
// @ref _?field_player_buildings_captured@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6170
// @ref _?field_player_buildings_killed@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6168
// @ref _?field_player_buildings_left@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6128
// @ref _?field_player_clan@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6198
// @ref _?field_player_color@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f60f8
// @ref _?field_player_completion@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6188
// @ref _?field_player_country@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6100
// @ref _?field_player_crates_found@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6178
// @ref _?field_player_credits@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6108
// @ref _?field_player_handle@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f60e0
// @ref _?field_player_harvested@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6180
// @ref _?field_player_infantry_bought@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6138
// @ref _?field_player_infantry_killed@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6158
// @ref _?field_player_infantry_left@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6118
// @ref _?field_player_ip@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6190
// @ref _?field_player_lost_connection@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f61a0
// @ref _?field_player_planes_bought@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6140
// @ref _?field_player_planes_killed@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6160
// @ref _?field_player_planes_left@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6120
// @ref _?field_player_t_team@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f60f0
// @ref _?field_player_team@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f60e8
// @ref _?field_player_units_bought@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6130
// @ref _?field_player_units_killed@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6150
// @ref _?field_player_units_left@?4??Unknown_00698D00@@YIX_N@Z@4PADA=007f6110
// @ref _?packet_size@?4??Unknown_00698D00@@YIX_N@Z@4HA=00abd518
// @ref ??_C@_04OHGB@UNIT?$AA@=007f3504
// @ref ??_C@_04CFJE@PROC?$AA@=007d20d0
