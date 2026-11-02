#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
#include "shared/multi_mission.hpp"
#include "shared/special.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??_C@_0BN@CALA@Sending?5game?5options?5packet?6?$AA@=007e25bc
// @ref ?Unknown_007131b0@VersionClass@@QAEKXZ=007131b0
// @ref ?Unknown_007131c0@VersionClass@@QAEKXZ=007131c0
// @ref ?Unknown_00737af0@@YAHXZ=00737af0
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_multi_missions_a3d8d8@@3V?$DynamicVectorClass@PAVMultiMission@@@@A=00a3d8d8
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_special_a40920@@3VSpecialClass@@A=00a40920
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?version_object_00a40c88@@3VVersionClass@@A=00a40c88
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" char *__cdecl strncpy(char *dest, char const *source, unsigned int count);

void ModemHost::Send_Options_0059bc90()
{
    Debug_Printf("Sending game options packet\n");
    EnableWindow(GetDlgItem(Window, 1), 0);
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x65;
    packet.Options.Checksum = unknown_54;
    packet.Options.ArtID = unknown_58;
    packet.Options.INIID = unknown_5c;
    packet.Options.Version = Unknown_00737af0();
    packet.Options.MinVersion = version_object_00a40c88.Unknown_007131b0();
    packet.Options.MaxVersion = version_object_00a40c88.Unknown_007131c0();
    packet.Options.Seed = Seed;
    packet.Options.Special = unknown_special_a40920;
    packet.Options.GameSpeed = unknown_session_a3d298.GameSpeed_30;
    packet.Options.unknown_2a = unknown_session_a3d298.unknown_2a;
    packet.Options.unknown_2b = unknown_session_a3d298.unknown_2b;
    packet.Options.unknown_2c = unknown_session_a3d298.unknown_2c;
    packet.Options.unknown_34 = unknown_session_a3d298.unknown_34;
    packet.ID = serial_local_player_00a3fb38;
    strcpy(packet.Name, unknown_name_a3d3a0);
    packet.Options.House = unknown_a3d3bc;
    packet.Options.Color = unknown_a3d3b4;
    packet.Options.Credits = unknown_session_a3d298.unknown_24;
    packet.Options.Bases = unknown_session_a3d298.unknown_bases_20;
    packet.Options.unknown_a8 = unknown_session_a3d298.unknown_a8;
    packet.Options.unknown_28 = unknown_session_a3d298.unknown_28;
    packet.Options.Crates = unknown_session_a3d298.unknown_crates_29;
    packet.Options.unknown_a5 = unknown_session_a3d298.unknown_a5;
    packet.Options.FogOfWar = unknown_session_a3d298.unknown_fog_a7;
    packet.Options.AICount = unknown_session_a3d298.AICount;
    packet.Options.AIDifficulty = unknown_session_a3d298.unknown_difficulty_40;
    packet.Options.TechLevel = unknown_house_setting_7d88d8;
    packet.Options.UnitCount = unknown_session_a3d298.UnitCount;
    wcscpy(packet.Options.MapName, unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Description);
    CCFileClass file(unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Get_Filename());
    packet.Options.FileLength = file.Size();
    strncpy(packet.Options.FileName, unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Get_Filename(), 13);
    strncpy(packet.Options.Digest, unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Get_Digest(), 0x20);
    packet.Options.IsOfficial = unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Get_Official();
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
}
