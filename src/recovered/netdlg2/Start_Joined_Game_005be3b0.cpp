// bool __fastcall Start_Joined_Game_005be3b0(int unknown) (0x005BE3B0; the argument is unused: Net_Join_Dialog 0x005BD070 passes 0 for join state 3 and 1 for state 4 and declares it)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/debug_printf.hpp"
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_0BH@NCIJ@TXT_UNABLE_PLAY_WAAUGH?$AA@=007e2184
// @ref ??_C@_0CH@KMCI@Found?5local?5scenario?0?5file?5name?5@=007e6c24
// @ref ??_C@_0DA@FCOD@Failed?5to?5find?5local?5scenario?0?5f@=007e6bc0
// @ref ??_C@_0DD@CJFE@IPX?4Global_Response_Time?$CI?$CJ?5?$DN?$DN?5?$CFd@=007e6bf0
// @ref ?Find_Local_Scenario_0066c5b0@@YI_NPADH0_N1@Z=0066c5b0
// @ref ?Get_File_From_Host_0066aef0@@YI_NPADH_N@Z=0066aef0
// @ref ?Unknown_00672140@UnknownSessionState@@QAE_NXZ=00672140
// @ref ?unknown_chat_a3fa4c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa4c
// @ref ?unknown_session_a3d298.ScenarioDigest_85a@@3PADA=00a3daf2
// @ref ?unknown_session_a3d298.ScenarioFileName_658@@3PADA=00a3d8f0
// @ref ?unknown_session_a3d298.ScenarioFileLength_87c@@3HA=00a3db14
// @ref ?unknown_session_a3d298.ScenarioIsOfficial_880@@3_NA=00a3db18
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4

bool __fastcall Start_Joined_Game_005be3b0(int unknown)
{
    unknown_ipx_manager_a40978.Set_Timing(unknown_ipx_manager_a40978.unknown_526c30() + 2 > 30 ? unknown_ipx_manager_a40978.unknown_526c30() + 2 : 30,
        -1, 1000, true);
    if (Find_Local_Scenario_0066c5b0(unknown_session_a3d298.ScenarioFileName_658, unknown_session_a3d298.ScenarioFileLength_87c, unknown_session_a3d298.ScenarioDigest_85a,
            unknown_session_a3d298.ScenarioIsOfficial_880, true) == true) {
        Debug_Printf("Found local scenario, file name is %d\n", unknown_session_a3d298.ScenarioFileName_658);
        UnknownGlobalPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 0x13;
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3db2c, 0, 0);
        while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && unknown_ipx_manager_a40978.Service() != 0) {
            Service_Game_IO_00481fb0();
        }
    } else {
        Debug_Printf("Failed to find local scenario, file name is %d\n", unknown_session_a3d298.ScenarioFileName_658);
        if ((unknown_session_a3d298.ScenarioIsOfficial_880 && !unknown_session_a3d298.Unknown_00672140())
            || !Get_File_From_Host_0066aef0(unknown_session_a3d298.ScenarioFileName_658, 3, true)) {
            unknown_session_a3d2b4 = -1;
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_PLAY_WAAUGH", 0, "D:\\Ra2\\netdlg2.cpp", 678),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\netdlg2.cpp", 678), 0, 0, false);
            UnknownGlobalPacket packet;
            memset(&packet, 0, sizeof(packet));
            packet.Command = 10;
            strcpy(packet.Name, unknown_name_a3d3a0);
            for (int i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_chat_a3fa4c[i]->Address, 0, 0);
                Service_Game_IO_00481fb0();
            }
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
            if (unknown_dest_net_set_a3f604) {
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
            }
            while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && unknown_ipx_manager_a40978.Service() != 0) {
                Service_Game_IO_00481fb0();
            }
            return false;
        }
    }
    strcpy(unknown_id_source_a3d290->FileName, unknown_session_a3d298.ScenarioFileName_658);
    int response = unknown_ipx_manager_a40978.unknown_526c30();
    if (response < 20) {
        Debug_Printf("IPX.Global_Response_Time() == %d. Adjusting to 20\n", response);
        response = 20;
    }
    unknown_ipx_manager_a40978.Set_Timing(response, -1, response * 8 < 120 ? 120 : response * 8, true);
    unknown_ipx_manager_a40978.unknown_slot14(60, -1, 600);
    return true;
}
