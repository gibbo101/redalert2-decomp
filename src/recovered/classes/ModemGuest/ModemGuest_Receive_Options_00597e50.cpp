// ModemGuest::Receive_Options_00597e50 (0x00597E50)
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/modem_guest.hpp"
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
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/multi_mission.hpp"
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
// @ref ??_C@_0BG@JFGK@Scenario?5has?5changed?6?$AA@=007e2264
// @ref ??_C@_0BH@OIIO@Decoding?5game?5options?6?$AA@=007e227c
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ?Compare_Narrow_00781f20@@YAHPBD0@Z=00781f20
// @ref ?Unknown_0068B410@SpecialClass@@QAEXXZ=0068b410
// @ref ?Equals_Options@SpecialClass@@QBE_NABV1@@Z=0068b3f0
// @ref ?unknown_a40b18@@3HA=00a40b18
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_map_name_a3d342@@3PAGA=00a3d342
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_multi_missions_a3d8d8@@3V?$DynamicVectorClass@PAVMultiMission@@@@A=00a3d8d8
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_special_a40920@@3VSpecialClass@@A=00a40920
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);

bool ModemGuest::Receive_Options_00597e50(UnknownSerialPacket const *packet)
{
    if (unknown_session_a3d298.unknown_bases_20 == (bool)packet->Options.Bases
        && unknown_session_a3d298.unknown_a8 == (bool)packet->Options.unknown_a8
        && unknown_session_a3d298.unknown_a5 == (bool)packet->Options.unknown_a5
        && unknown_session_a3d298.unknown_28 == (bool)packet->Options.unknown_28
        && unknown_session_a3d298.unknown_crates_29 == (bool)packet->Options.Crates
        && unknown_session_a3d298.unknown_fog_a7 == (bool)packet->Options.FogOfWar
        && unknown_session_a3d298.AICount == packet->Options.AICount
        && unknown_session_a3d298.unknown_difficulty_40 == packet->Options.AIDifficulty
        && unknown_house_setting_7d88d8 == packet->Options.TechLevel
        && unknown_session_a3d298.unknown_24 == packet->Options.Credits
        && unknown_session_a3d298.UnitCount == packet->Options.UnitCount
        && Seed == packet->Options.Seed
        && unknown_special_a40920.Equals_Options(packet->Options.Special)
        && unknown_session_a3d298.GameSpeed_30 == packet->Options.GameSpeed
        && unknown_session_a3d298.unknown_2a == (bool)packet->Options.unknown_2a
        && unknown_session_a3d298.unknown_2b == (bool)packet->Options.unknown_2b
        && unknown_session_a3d298.unknown_2c == (bool)packet->Options.unknown_2c
        && unknown_session_a3d298.unknown_34 == (bool)packet->Options.unknown_34
        && !Compare_Narrow_00781f20(unknown_session_a3d298.ScenarioFileName_658, packet->Options.FileName)
        && !strcmp(unknown_session_a3d298.ScenarioDigest_85a, packet->Options.Digest)
        && unknown_session_a3d298.ScenarioFileLength_87c == packet->Options.FileLength) {
        return false;
    }
    Debug_Printf("Decoding game options\n");
    unknown_session_a3d298.unknown_bases_20 = packet->Options.Bases;
    unknown_session_a3d298.unknown_a8 = packet->Options.unknown_a8;
    unknown_session_a3d298.unknown_28 = packet->Options.unknown_28;
    unknown_special_a40920.DestroyableBridges = packet->Options.unknown_28;
    unknown_session_a3d298.unknown_crates_29 = packet->Options.Crates;
    unknown_session_a3d298.unknown_fog_a7 = packet->Options.FogOfWar;
    unknown_session_a3d298.unknown_a5 = packet->Options.unknown_a5;
    unknown_session_a3d298.AICount = packet->Options.AICount;
    unknown_session_a3d298.unknown_difficulty_40 = packet->Options.AIDifficulty;
    unknown_house_setting_7d88d8 = packet->Options.TechLevel;
    unknown_session_a3d298.unknown_24 = packet->Options.Credits;
    unknown_session_a3d298.UnitCount = packet->Options.UnitCount;
    Seed = packet->Options.Seed;
    unknown_special_a40920 = packet->Options.Special;
    unknown_a40b18 = unknown_session_a3d298.GameSpeed_30 = packet->Options.GameSpeed;
    unknown_session_a3d298.unknown_2a = packet->Options.unknown_2a;
    unknown_session_a3d298.unknown_2b = packet->Options.unknown_2b;
    unknown_session_a3d298.unknown_2c = packet->Options.unknown_2c;
    unknown_session_a3d298.unknown_34 = packet->Options.unknown_34;
    unknown_special_a40920.TiberiumGrows = true;
    unknown_special_a40920.TiberiumSpreads = true;
    unknown_id_source_a3d290->Special().FixedAlliance = false;
    unknown_session_a3d298.unknown_a4 = true;
    unknown_special_a40920.Unknown_0068B410();
    if (Compare_Narrow_00781f20(unknown_session_a3d298.ScenarioFileName_658, packet->Options.FileName)
        || Compare_Narrow_00781f20(unknown_session_a3d298.ScenarioDigest_85a, packet->Options.Digest)
        || unknown_session_a3d298.ScenarioIsOfficial_880 != (bool)packet->Options.IsOfficial
        || unknown_session_a3d298.ScenarioFileLength_87c != packet->Options.FileLength
        || !unknown_map_name_a3d342[0]) {
        Debug_Printf("Scenario has changed\n");
        strcpy(unknown_session_a3d298.ScenarioFileName_658, packet->Options.FileName);
        strcpy(unknown_session_a3d298.ScenarioDigest_85a, packet->Options.Digest);
        unknown_session_a3d298.ScenarioIsOfficial_880 = packet->Options.IsOfficial;
        unknown_session_a3d298.ScenarioFileLength_87c = packet->Options.FileLength;
        bool found = false;
        if (strcmp(unknown_session_a3d298.ScenarioFileName_658, "RandMap.Sed") || !unknown_session_a3d298.ScenarioIsOfficial_880) {
            for (int index = 0; index < unknown_multi_missions_a3d8d8.Count(); index++) {
                MultiMission *mission = unknown_multi_missions_a3d8d8[index];
                if (!Compare_Narrow_00781f20(unknown_session_a3d298.ScenarioFileName_658, mission->unknown_58)) {
                    wcscpy(unknown_map_name_a3d342, mission->Description);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            wcscpy(unknown_map_name_a3d342, packet->Options.MapName);
        }
        if (unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
        }
    }
    return true;
}
