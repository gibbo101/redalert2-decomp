// Read_Scenario_Descriptions00670C50: register maps from packet lists, archives and loose files.
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cd.hpp"
#include "shared/win32_find.hpp"
#include "shared/crt_string.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
extern "C" char const session_missing_packet[];
// @ref _session_missing_packet=007f39a0
extern "C" wchar_t *__cdecl wcsncat(wchar_t *, wchar_t const *, unsigned int);
void __fastcall Unknown_006FA0C0(wchar_t *buffer, char const *text, int length);
void __fastcall Read_Map_Header_006707d0(char const *, unsigned short *, char *, char *, bool *, int *, int *);
// @ref _wcsncat=00784704
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ?Set_Description_00671FA0@MultiMission@@QAEXPBG@Z=00671fa0
extern "C" char const session_missions[];
// @ref _session_missions=007f3a28
extern "C" char const session_maps[];
// @ref _session_maps=007f3a1c
extern "C" char const session_pkt_pattern[];
// @ref _session_pkt_pattern=007f3a14
extern "C" char const session_mmx_pattern[];
// @ref _session_mmx_pattern=007f3a0c
extern "C" char const session_base_mmx[];
// @ref _session_base_mmx=007f39fc
extern "C" char const session_pkt_ext[];
// @ref _session_pkt_ext=007f39f8
extern "C" char const session_mpr_pattern[];
// @ref _session_mpr_pattern=007f3998
extern "C" wchar_t const session_range_format[];
// @ref _session_range_format=007f39e4
extern "C" wchar_t const session_single_format[];
// @ref _session_single_format=007f39d4
extern "C" wchar_t const session_space[];
// @ref _session_space=007d64f4
extern "C" char const session_empty[];
// @ref _session_empty=0083c55c
extern "C" char const session_basic[];
// @ref _session_basic=007e1a50
extern "C" char const session_name[];
// @ref _session_name=007ce2a4
extern "C" char const session_no_name[];
// @ref _session_no_name=007dee7c
extern "C" char const session_digest[];
// @ref _session_digest=007d1ef0
extern "C" char const session_one[];
// @ref _session_one=007e6f6c
extern "C" char const session_no_digest[];
// @ref _session_no_digest=007f38ec
extern "C" char const session_official[];
// @ref _session_official=007f21d0
extern "C" char const session_no_description[];
// @ref _session_no_description=007f39c0
extern "C" char const session_source_file[];
// @ref _session_source_file=007f33c8

inline void MultiMission::Set_Description_00671FA0(unsigned short const *text)
{
    if (text != 0) {
        wcsncpy(Description, text, 44);
        Description[43] = 0;
        return;
    }
    wcscpy(Description, StringTable::Load_String(session_no_description, 0, session_source_file, 2826));
}

void UnknownSessionState::Read_Scenario_Descriptions()
{
    INIClass ini;
    char name_buffer[64];
    char digest_buffer[32];
    wchar_t description[44];
    WIN32_FIND_DATA block;
    wchar_t player_text[64];
    wchar_t wide_name[64];
    char packet_name[260];
    char modes[256];
    int min_players;
    int max_players;

    Scenarios.Clear();
    CCFileClass file(session_missions);
    if (file.Is_Available()) {
        ini.Load(file, false);
        int count = ini.Entry_Count(session_maps);
        for (int index = 0; index < count; index++) {
            if (ini.Get_String(session_maps, ini.Get_Entry(session_maps, index), session_empty, name_buffer, sizeof(name_buffer))) {
                Scenarios.Add(new MultiMission(ini, name_buffer));
            }
        }
    }
    ini.Clear();
    file.Close();
    HANDLE handle = FindFirstFileA(session_pkt_pattern, &block);
    if (handle != (HANDLE)-1) {
        do {
            if (!(block.dwFileAttributes & 0x116)) {
                char const *filename = block.cAlternateFileName;
                if (strlen(filename) == 0) filename = block.cFileName;
                if (_stricmp(filename, session_missions)) {
                    file.Set_Name(filename);
                    ini.Load(file, false);
                    int count = ini.Entry_Count(session_maps);
                    for (int index = 0; index < count; index++) {
                        if (ini.Get_String(session_maps, ini.Get_Entry(session_maps, index), session_empty, name_buffer, sizeof(name_buffer))) {
                            Scenarios.Add(new MultiMission(ini, name_buffer));
                        }
                    }
                }
            }
        } while (FindNextFileA(handle, &block));
        FindClose(handle);
    }
    ini.Clear();
    file.Close();
    handle = FindFirstFileA(session_mmx_pattern, &block);
    int required_cd = CD::RequiredCD;
    CD::Set_Required_CD(-2);
    if (handle != (HANDLE)-1) {
        do {
            if (!(block.dwFileAttributes & 0x116)) {
                char const *filename = block.cAlternateFileName;
                if (strlen(filename) == 0) filename = block.cFileName;
                if (_stricmp(filename, session_base_mmx)) {
                    MixFileClass *archive = new MixFileClass(filename, &FastKey);
                    if (archive != 0) {
                        unknown_mixes_837480.Add(archive);
                        int length = strlen(filename);
                        strncpy(packet_name, filename, length - 3);
                        packet_name[length - 3] = 0;
                        strcat(packet_name, session_pkt_ext);
                        packet_name[length] = 0;
                        file.Set_Name(packet_name);
                        if (file.Is_Available()) {
                            ini.Load(file, false);
                            int count = ini.Entry_Count(session_maps);
                            for (int index = 0; index < count; index++) {
                                if (ini.Get_String(session_maps, ini.Get_Entry(session_maps, index), session_empty, name_buffer, sizeof(name_buffer))) {
                                    MultiMission *mission = new MultiMission(ini, name_buffer);
                                    if (mission != 0) {
                                        if (mission->Get_Min_Players() != mission->Get_Max_Players()) {
                                            swprintf(player_text, session_range_format, '(', mission->Get_Min_Players(), mission->Get_Max_Players(), ')');
                                        } else {
                                            swprintf(player_text, session_single_format, '(', mission->Get_Min_Players(), ')');
                                        }
                                        int used = wcslen(mission->Description);
                                        wcscpy(description, mission->Description);
                                        wcsncat(description, session_space, 44 - used);
                                        int &used_count = used;
                                        ++used_count;
                                        wcsncat(description, player_text, 44 - used);
                                        mission->Set_Description_00671FA0(description);
                                        Scenarios.Add(mission);
                                    }
                                }
                            }
                            ini.Clear();
                        } else {
                            Debug_Printf(session_missing_packet);
                        }
                    }
                }
            }
        } while (FindNextFileA(handle, &block));
    }
    CD::Set_Required_CD(required_cd);
    if (handle != (HANDLE)-1) FindClose(handle);
    ini.Clear();
    file.Close();
    handle = FindFirstFileA(session_mpr_pattern, &block);
    bool official = false;
    if (handle != (HANDLE)-1) {
        do {
            if (!(block.dwFileAttributes & 0x116)) {
                char const *filename = block.cAlternateFileName;
                if (strlen(filename) == 0) filename = block.cFileName;
                ini.Get_String(session_basic, session_name, session_no_name, name_buffer, sizeof(name_buffer));
                ini.Get_String(session_digest, session_one, session_no_digest, digest_buffer, sizeof(digest_buffer));
                Unknown_006FA0C0(wide_name, name_buffer, -1);
                official = ini.Get_Bool(session_basic, session_official, false);
                min_players = 2;
                max_players = 4;
                Read_Map_Header_006707d0(filename, wide_name, digest_buffer, modes, &official, &min_players, &max_players);
                Scenarios.Add(new MultiMission(filename, wide_name, digest_buffer, official, modes, min_players, max_players));
            }
        } while (FindNextFileA(handle, &block));
        FindClose(handle);
    }
}
