// ModemHost::Dialog_Proc_00598fa0 (0x00598FA0): TibSun modemhst.cpp Modem_Host_Dialog_Proc (outer case order
// WM_COMMAND, WM_HSCROLL/VSCROLL, WM_DESTROY, WM_PAINT). The /Ob2 budget matches the original only with the
// chat chain (Send_Chat 0x59A880 -> 0x59BFA0 -> Show_Chat 0x59C0B0 calls) and the checkbox readers' named
// state/checked locals: Read_Unit_Count inlines, Read_Tech_Level and ??_G 0x59CB80 stay calls.
// @ref ?Select_Multi_Map_0059b090@ModemHost@@QAEXXZ=0059b090
// @ref ??_GUnknownPreview_0061D430@@QAEPAXI@Z=0059cb80
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/modem_host.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/lobby.hpp"
#include "shared/trigger_type.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/id_source.hpp"
#include "shared/modem_guest.hpp"
#include "shared/cd_timer.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/buffer_pipe.hpp"
#include "shared/lzo_pipe.hpp"
#include "shared/null_modem.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/campaign.hpp"
#include "shared/special.hpp"
#include "shared/random2.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/multi_mission.hpp"
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ?unknown_modem_host_a70de4@@3PAVModemHost@@A=00a70de4
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__ShowWindow@8=0079a498
// @ref ?Dialog_Proc_00598fa0@ModemHost@@SGHPAUHWND__@@IIJ@Z=00598fa0
// @ref ?Init_Dialog_00599920@ModemHost@@QAEXXZ=00599920
// @ref ?Start_Game_0059c290@ModemHost@@QAE_N_N@Z=0059c290
// @ref ?Service_0059b560@ModemHost@@QAEX_N@Z=0059b560
// @ref ?Process_Messages_0059b690@ModemHost@@QAE_N_N@Z=0059b690
// @ref ?Sign_Off_0059c130@ModemHost@@QAEXXZ=0059c130
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BJ@HKPJ@ModemHost?4Dialog?$CIenter?$CJ?6?$AA@=007e2430
// @ref ??_C@_0BL@ENPP@ModemHost?4Dialog?$CIexit?5?$CFs?$CJ?6?$AA@=007e2414
// @ref ?Clip_Version_00713170@VersionClass@@QAEHKK@Z=00713170
// @ref ?Version_Protocol_00713130@VersionClass@@QAEHH@Z=00713130
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BB@BKJO@Received?5packet?6?$AA@=007e20c4
// @ref ??_C@_0BD@NMJA@Received?5SignOff?$CB?6?$AA@=007e2588
// @ref ??_C@_0BE@EBDB@D?3?2Ra2?2ModemHst?4cpp?$AA@=007e247c
// @ref ??_C@_0BE@IJFA@TXT_USER_SIGNED_OFF?$AA@=007e2204
// @ref ??_C@_0BG@HINH@TXT_YOURGAME_OUTDATED?$AA@=007e21bc
// @ref ??_C@_0BG@LMNF@TXT_DESTGAME_OUTDATED?$AA@=007e21d4
// @ref ??_C@_0BH@HLKP@Received?5game?5options?6?$AA@=007e21ec
// @ref ??_C@_0BI@GJDM@Received?5timing?5packet?6?$AA@=007e2120
// @ref ??_C@_0BJ@KHMC@Received?5Accept?5Options?6?$AA@=007e256c
// @ref ??_C@_0BJ@KLKI@Received?5serial?5message?6?$AA@=007e2138
// @ref ??_C@_0BK@GPBE@TXT_SYSTEM_NOT_RESPONDING?$AA@=007e222c
// @ref ??_C@_0BO@DHPD@Received?5our?5own?5packet?5back?6?$AA@=007e259c
// @ref ??_C@_0BO@MNHL@Received?5score?5screen?5packet?6?$AA@=007e2100
// @ref ??_C@_0CP@GEMF@Timeout?$CB?5?$CFd?5ticks?5since?5last?5inc@=007e2154
// @ref ??_C@_0N@BAAD@TXT_MISMATCH?$AA@=007e21ac
// @ref ?Send_Preview_0059c8b0@ModemHost@@QAEXXZ=0059c8b0
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Set_Guest_0059ab80@ModemHost@@QAEXPBGHH@Z=0059ab80
// @ref ?Show_Chat_0059c0b0@ModemHost@@QAEXPBGH0@Z=0059c0b0
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_session_a3d2ac@@3HA=00a3d2ac
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?version_object_00a40c88@@3VVersionClass@@A=00a40c88
// @ref? ??_C@_13ECNF@?$AA?5?$AA?$AA@ hits 007a0190 007a01f0 007a0250 007a02b0 007a0310
// Read_AI_Difficulty_0059ad80 (0x0059AD80)
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// Read_AI_Players_0059ad10 (0x0059AD10)
// Read_Bases_0059adf0 (0x0059ADF0)
// @ref __imp__SendDlgItemMessageA@20=0079a484
// Read_Bridge_Destroy_0059aee0 (0x0059AEE0)
// Read_Color_0059aa80 (0x0059AA80)
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_color_7a737c@@3HA=007a737c
// Read_Color_Entry_0059aa20 (0x0059AA20)
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// Read_Crap_Engineers_0059b050 (0x0059B050)
// Read_Crates_0059ae60 (0x0059AE60)
// Read_Credits_0059ace0 (0x0059ACE0)
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?Unknown_005c6600@@YIHH@Z=005c6600
// @ref ?Unknown_006FA0F0@@YIXPADPBGH@Z=006fa0f0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ??_C@_02HAKO@ON?$AA@=007e1f40
// @ref ??_C@_03CMJG@OFF?$AA@=007e1f3c
// @ref ??_C@_0BA@DOI@Game?5Speed?3?5?$CFd?6?$AA@=007e1f58
// @ref ??_C@_0BA@NBOO@Short?5Game?3?5?$CFs?6?$AA@=007e1f0c
// @ref ??_C@_0BB@ILLA@MCVRedeploy?3?5?$CFs?6?$AA@=007e1f28
// @ref ??_C@_0BC@DPJ@AIDifficulty?3?5?$CFd?6?$AA@=007e1f44
// @ref ??_C@_0BD@ODLN@BridgeDestroy?3?5?$CFs?6?$AA@=007e1ea0
// @ref ??_C@_0BE@KMDF@Crap?5Engineers?3?5?$CFs?6?$AA@=007e1ed0
// @ref ??_C@_0BF@CBAA@Harvester?5Truce?3?5?$CFs?6?$AA@=007e1e88
// @ref ??_C@_0BH@KOPH@TXT_SCENARIO_TOO_SMALL?$AA@=007e24cc
// @ref ??_C@_0BM@IDBK@ModemHost?4ReadDialog?$CIexit?$CJ?6?$AA@=007e24b0
// @ref ??_C@_0BN@MDII@ModemHost?4ReadDialog?$CIenter?$CJ?6?$AA@=007e24e4
// @ref ??_C@_0L@DFNB@Name?3?5?$CFls?6?$AA@=007e2028
// @ref ??_C@_0L@HPID@Color?3?5?$CFd?6?$AA@=007e1fa8
// @ref ??_C@_0L@ODDO@Bases?3?5?$CFs?6?$AA@=007e1f1c
// @ref ??_C@_0M@IDPK@Crates?3?5?$CFs?6?$AA@=007e1ec4
// @ref ??_C@_0N@KDNE@Credits?3?5?$CFd?6?$AA@=007e1f78
// @ref ??_C@_0O@BKAD@FogOfWar?3?5?$CFs?6?$AA@=007e1eb4
// @ref ??_C@_0P@DJIC@AIPlayers?3?5?$CFd?6?$AA@=007e1f68
// @ref ??_C@_0P@LIHP@UnitCount?3?5?$CFd?6?$AA@=007e1f98
// @ref ??_C@_0P@ONCE@TechLevel?3?5?$CFd?6?$AA@=007e1f88
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);
// Read_Fog_Of_War_0059aea0 (0x0059AEA0)
// Read_Game_Speed_0059ad40 (0x0059AD40)
// Read_Harvester_Truce_0059af20 (0x0059AF20)
// Read_MCV_Redeploy_0059adb0 (0x0059ADB0)
// Read_Name_0059aaf0 (0x0059AAF0)
// Read_Short_Game_0059af60 (0x0059AF60)
// Read_Short_Game_0059b010 (0x0059B010)
// Read_Tech_Level_0059acb0 (0x0059ACB0)
// Read_Unit_Count_0059ac80 (0x0059AC80)
// Read_unknown_2b_0059afd0 (0x0059AFD0)
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern unsigned short const unknown_empty_wide_839d4c[];
// @ref ??_C@_0BK@LFJL@Preview?5size?5is?5?$CFd?5bytes?6?$AA@=007e2754
// @ref ??_C@_0BN@KJJF@Starting?5map?5preview?5upload?6?$AA@=007e2794
// @ref ??_C@_0CC@GEGD@Failed?5to?5get?5SERIAL_PREVIEW_ACK@=007e2770
// @ref ??_C@_0CG@PAND@Compressed?5preview?5image?5is?5?$CFd?5b@=007e272c
// @ref ??_C@_0CO@INCK@Calling?5Send_Remote_File?5to?5send@=007e26f0
// @ref ??_C@_0M@CNHP@Preview?4bin?$AA@=007e2720
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ?Compare_Narrow_00781f20@@YAHPBD0@Z=00781f20
// @ref ?Send_Remote_File_0066bb20@@YI_NPBDHHH@Z=0066bb20
// @ref ?Unknown_0061E490@UnknownPreview_0061D430@@QAEPAGHPAH@Z=0061e490
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ??_7BufferPipe@@6B@=0079ea08
// @ref ?Send_Options_0059bc90@ModemHost@@QAEXXZ=0059bc90
// Set_Guest_0059ab80 (0x0059AB80)
// @ref ??_C@_1BA@DLOG@?$AA?$CF?$AAs?$AA?5?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?$AA@=007e20a0
extern "C" int __cdecl _wcsicmp(unsigned short const *left, unsigned short const *right);
// @ref ??_C@_0BA@JILO@TXT_SIGNING_OFF?$AA@=007e2294
extern "C" void __cdecl srand(unsigned int seed);
extern "C" int __cdecl rand();
// @ref ?unknown_modem_host_first_7e2410@@3_NA=007e2410
// @ref ?Unknown_0068B420@SpecialClass@@QAEXXZ=0068b420
// @ref ?Unknown_0061E2A0@UnknownPreview_0061D430@@QAEXPBD@Z=0061e2a0
// @ref ??_C@_07NKKE@TXT_RED?$AA@=007e2000
// @ref ??_C@_08LPFB@TXT_PINK?$AA@=007e1fb4
// @ref ??_C@_08NALB@TXT_GOLD?$AA@=007e2008
// @ref ??_C@_08PFFA@TXT_BLUE?$AA@=007e1ff4
// @ref ??_C@_09KDHI@TXT_GREEN?$AA@=007e1fe8
// @ref ??_C@_0BC@BBEC@SuperWeapons?3?5?$CFs?6?$AA@=007e1ef8
// @ref ??_C@_0BC@IEEF@BuildOffAlly?3?5?$CFs?6?$AA@=007e1ee4
// @ref ??_C@_0BC@PEFB@MCV?5Redeploy?3?5?$CFs?6?$AA@=007e2468
// @ref ??_C@_0BM@CM@ModemHost?4InitDialog?$CIexit?$CJ?6?$AA@=007e244c
// @ref ??_C@_0BN@JEAL@ModemHost?4InitDialog?$CIenter?$CJ?6?$AA@=007e2490
// @ref ??_C@_0L@EPJB@TXT_ORANGE?$AA@=007e1fdc
// @ref ??_C@_0L@NJNM@TXT_PURPLE?$AA@=007e1fc0
// @ref ??_C@_0N@GNAA@TXT_SKY_BLUE?$AA@=007e1fcc
// @ref ?Find_Combo_Item_Data_00736e10@@YIHPAUHWND__@@HH@Z=00736e10
// @ref ?Init_Clipping_00713160@VersionClass@@QAEXXZ=00713160
// @ref __imp__PostMessageA@16=0079a470
// @ref ??_C@_0BC@FOEB@Received?5message?6?$AA@=007e2674
// @ref ??_C@_0BF@BAJ@Received?5GO?5message?6?$AA@=007e265c
// @ref ??_C@_0BK@MEMK@TXT_NO_EXPANSION_SCENARIO?$AA@=007e2640
// @ref ??_C@_0BL@MMBK@ModemHost?4StartGame?$CIexit?$CJ?6?$AA@=007e25dc
// @ref ??_C@_0BM@CEMH@ModemHost?4StartGame?$CIenter?$CJ?6?$AA@=007e26d4
// @ref ??_C@_0BM@FKCC@Waiting?5for?5?8GO?8?5response?4?6?$AA@=007e2688
// @ref ??_C@_0CB@OOII@?$CK?$CK?$CKGuest?5doesn?8t?5have?5scenario?$CB?6@=007e261c
// @ref ??_C@_0CD@LJGE@About?5to?5call?5?8Send_Remote_File?8@=007e25f8
// @ref ??_C@_0P@FLNF@TXT_WAITING_GO?$AA@=007e26a4
// @ref ??_C@_0P@HMGP@TXT_SENDING_GO?$AA@=007e26b4
// @ref ??_C@_0P@OCIN@LoadGame?5?$DN?5?$CFs?6?$AA@=007e26c4
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8


int __stdcall ModemHost::Dialog_Proc_00598fa0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) {
        return result;
    }
    ModemHost *host = (ModemHost *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x111:
        switch ((unsigned short)wparam) {
        case 1:
            if ((unsigned short)(wparam >> 16) == 0 && host->Read_Dialog_0059a310() == true) {
                host->Send_Options_0059bc90();
                host->Result = 1;
            }
            break;
        case 2:
            if ((unsigned short)(wparam >> 16) == 0) {
                host->Read_Dialog_0059a310();
                host->Result = 2;
            }
            break;
        case 0x405:
            if ((unsigned short)(wparam >> 16) == 1) {
                host->Read_Color_0059aa80();
            }
            break;
        case 0x540:
            if ((unsigned short)(wparam >> 16) == 0x501) {
                host->Send_Chat_0059a880();
            }
            break;
        case 0x54C:
            host->Read_Crates_0059ae60();
            break;
        case 0x54D:
            host->Read_Fog_Of_War_0059aea0();
            break;
        case 0x54E:
            host->Read_Short_Game_0059af60();
            break;
        case 0x551:
            host->Read_Crap_Engineers_0059b050();
            break;
        case 0x596:
            host->Read_Harvester_Truce_0059af20();
            break;
        case 0x667:
            if ((unsigned short)(wparam >> 16) == 1) {
                host->Read_Color_Entry_0059aa20();
            }
            break;
        case 0x5C1:
            if ((unsigned short)(wparam >> 16) == 0x501 || (unsigned short)(wparam >> 16) == 0x300) {
                host->Read_Name_0059aaf0((unsigned short)(wparam >> 16) == 0x300);
            }
            break;
        case 0x66B:
            host->Read_MCV_Redeploy_0059adb0();
            break;
        case 0x66A:
            host->Read_Bases_0059adf0();
            break;
        case 0x624:
            host->Read_Bridge_Destroy_0059aee0();
            break;
        case 0x69A:
            host->Read_unknown_2b_0059afd0();
            break;
        case 0x69D:
            host->Read_Short_Game_0059b010();
            break;
        case 0x5AA:
            if ((unsigned short)(wparam >> 16) == 0) {
                host->Select_Multi_Map_0059b090();
            }
            break;
        }
        break;
    case 0x114:
    case 0x115:
        if (GetDlgItem(window, 0x669) == (HWND)lparam) {
            host->Read_Unit_Count_0059ac80();
        } else if (GetDlgItem(window, 0x550) == (HWND)lparam) {
            host->Read_Tech_Level_0059acb0();
        } else if (GetDlgItem(window, 0x402) == (HWND)lparam) {
            host->Read_Credits_0059ace0();
        } else if (GetDlgItem(window, 0x552) == (HWND)lparam) {
            host->Read_AI_Players_0059ad10();
        } else if (GetDlgItem(window, 0x553) == (HWND)lparam) {
            host->Read_AI_Difficulty_0059ad80();
        } else if (GetDlgItem(window, 0x529) == (HWND)lparam) {
            host->Read_Game_Speed_0059ad40();
        }
        break;
    case 0x2:
        if (unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
        }
        break;
    case 0xF:
        if (unknown_dialog_preview_a72ce8) {
            unknown_dialog_preview_a72ce8->Draw_0061D460(window);
        }
        ValidateRect(window, 0);
        break;
    }
    return 0;
}
