// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// void CampaignScoreClass::Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time,
//     bool more, int difficulty, wchar_t const *name) -- 0x00466A50
// The DynamicVectorClass Delete members this function expands inline are enabled by the unit's first
// include (header statics 0x00465A00).
// @ref ?unknown_score_850504@@3_NA=00850504
// @ref ?unknown_score_time_850508@@3HA=00850508
// @ref ?unknown_score_difficulty_7d1480@@3HA=007d1480
// @ref ?unknown_score_count_85050c@@3HA=0085050c
// @ref ?unknown_score_flag_850510@@3_NA=00850510
// @ref ?unknown_score_name_850514@@3PAGA=00850514
// @ref ?unknown_score_list_850448@@3PAPAVMPlayerScoreType@@A=00850448
// @ref ?unknown_score_ready_8504c8@@3PA_NA=008504c8
// @ref ?unknown_score_controls_7d1498@@3PAY05HA=007d1498
// @ref ?unknown_global_packet_a3f640@@3UUnknownScorePacket@@A=00a3f640
// @ref ?unknown_global_length_a3f808@@3HA=00a3f808
// @ref ?unknown_global_address_a3f80c@@3VIPXAddressClass@@A=00a3f80c
// @ref ?unknown_global_product_a3f818@@3GA=00a3f818
// @ref ?unknown_score_dialog_proc_465fc0@@YGHPAUHWND__@@IIJ@Z=00465fc0
// @ref ?unknown_465d10@CampaignScoreClass@@QAEXXZ=00465d10
// @ref ?unknown_5c05f0@@YI_NPAUUnknownScorePacket@@PAVIPXAddressClass@@@Z=005c05f0
// @ref ?Unknown_Load_Art_Once_006F2710@@YIXH@Z=006f2710
// @ref ?Unknown_Free_Art_Flagged_006F2750@@YAXXZ=006f2750
// @ref ?unknown_compare_descending_60_00465f20@@YAHPBX0@Z=00465f20
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?Service@IPXManagerClass@@UAEHXZ=00525f60
// @ref ?Get_Global_Message@IPXManagerClass@@QAEHPAXPAHPAVIPXAddressClass@@PAG@Z=00525ab0
// @ref ?unknown_5259a0@IPXManagerClass@@QAEHPAXHHPBG@Z=005259a0
// @ref ?unknown_5277f0@IPXManagerClass@@QAEXXZ=005277f0
// @ref ?unknown_527800@IPXManagerClass@@QAEXXZ=00527800
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__EnableWindow@8=0079a490
// @ref _wcscpy=00783689
// @ref _wcscmp=007837d3
// @ref _qsort=00781d46
// @ref ??3@YAXPAX@Z=00781d3b
#include "shared/ms_message_box.hpp"
#include "shared/keyboard.hpp"
#include "shared/string_table.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/id_source.hpp"
#include "shared/lobby.hpp"
#include "shared/mplayer_score_type.hpp"
#include "shared/campaign_score.hpp"

extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
extern "C" int __cdecl wcscmp(wchar_t const *left, wchar_t const *right);
// @ref ??_C@_09IMGH@TXT_READY?$AA@=007d1610
// @ref ??_C@_0M@LCFM@TXT_ABORTED?$AA@=007d161c
// @ref ??_C@_0M@MHCJ@TXT_WAITING?$AA@=007d1628
// @ref ??_C@_0BE@LFCN@D?3?2Ra2?2CampScor?4cpp?$AA@=007d1584

// Tells the other players to continue (command 0x26).
static inline void Send_Continue()
{
    UnknownScorePacket packet;
    memset(&packet, 0, sizeof(packet));
    unknown_score_850504 = true;
    packet.Command = 0x26;
    strcpy(packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
    for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
        unknown_ipx_manager_a40978.unknown_5259a0(&packet, 0x2F, 1, unknown_players_a3fa7c[i]->Name);
        unknown_ipx_manager_a40978.Service();
    }
}

extern int unknown_score_count_85050c;
extern int unknown_score_controls_7d1498[8][6];
class IPXAddressClass;
extern UnknownScorePacket unknown_global_packet_a3f640;
extern int unknown_global_length_a3f808;
extern IPXAddressClass unknown_global_address_a3f80c;
extern unsigned short unknown_global_product_a3f818;
bool __fastcall unknown_5c05f0(UnknownScorePacket *packet, IPXAddressClass *address);

// Every GetDlgItem call goes through this code-free wrapper: it puts the GetDlgItem import in edi and
// EnableWindow in esi in the 0x24 branch (the Get_Item rule, VC6_MATCHING_NOTES).
static inline HWND Get_Item(HWND window, int id)
{
    return GetDlgItem(window, id);
}

void CampaignScoreClass::Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time, bool more,
    int difficulty, wchar_t const *name)
{
    unknown_score_count_85050c = scores.Count();
    unknown_score_time_850508 = time;
    unknown_score_difficulty_7d1480 = difficulty;
    wcscpy(unknown_score_name_850514, name);
    unknown_reset_ready_465f50(8);
    int i;
    for (i = 0; i < unknown_score_count_85050c; i++) {
        unknown_score_list_850448[i] = scores[i];
    }
    unknown_465d10();
    unknown_sort_session_scores_465ee0();
    Unknown_Load_Art_Once_006F2710(unknown_id_source_a3d290->unknown_2239 == false);
    unknown_5159b0(0, true);
    if (unknown_game_mode_a3d298 == 4) {
        unknown_ipx_manager_a40978.unknown_5277f0();
    }
    HWND window = unknown_create_dialog_5ff610(0xBC6, unknown_score_dialog_proc_465fc0, 0);
    int result = 0;
    if (window) {
        SetWindowLongA(window, 8, (LONG)&result);
        unknown_dialog_5ff7c0(window);
        while (result == 0 || result == 1) {
            Unknown_005B5EE0();
            if (result == 1) {
                for (i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
                    if (wcscmp(unknown_players_a3fa7c[0]->Name, unknown_score_list_850448[i]->Name) == 0) {
                        break;
                    }
                }
                if (unknown_score_flag_850510) {
                    unknown_score_ready_8504c8[i] = true;
                } else {
                    unknown_score_ready_8504c8[i] = false;
                }
                if (unknown_all_ready_465f80() && more) {
                    unknown_score_850504 = true;
                    Send_Score_Packet(0x26);
                    break;
                }
                if (!more) {
                    unknown_score_850504 = false;
                    break;
                }
                result = 0;
            }
            unknown_ipx_manager_a40978.Service();
            if (!unknown_ipx_manager_a40978.Get_Global_Message(&unknown_global_packet_a3f640, &unknown_global_length_a3f808,
                    &unknown_global_address_a3f80c, &unknown_global_product_a3f818)
                || unknown_global_product_a3f818 != 0xAA03
                || unknown_5c05f0(&unknown_global_packet_a3f640, &unknown_global_address_a3f80c)) {
                continue;
            }
            if (unknown_global_packet_a3f640.Command == 0x23) {
                for (i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
                    if (strcmp(unknown_global_packet_a3f640.Name, Unknown_006FA120(unknown_score_list_850448[i]->Name)) == 0) {
                        int id = unknown_score_controls_7d1498[i][0];
                        wchar_t const *text = StringTable::Load_String("TXT_READY", 0, "D:\\Ra2\\CampScor.cpp", 582);
                        HWND item = Get_Item(window, id);
                        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
                        unknown_score_ready_8504c8[i] = true;
                        break;
                    }
                }
                if (unknown_all_ready_465f80() && more) {
                    unknown_score_850504 = true;
                    Send_Score_Packet(0x26);
                    break;
                }
            } else if (unknown_global_packet_a3f640.Command == 0x24) {
                for (i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
                    if (strcmp(unknown_global_packet_a3f640.Name, Unknown_006FA120(unknown_score_list_850448[i]->Name)) == 0) {
                        int id = unknown_score_controls_7d1498[i][0];
                        wchar_t const *text = StringTable::Load_String("TXT_ABORTED", 0, "D:\\Ra2\\CampScor.cpp", 602);
                        HWND item = Get_Item(window, id);
                        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
                        unknown_score_ready_8504c8[i] = false;
                        break;
                    }
                }
                for (i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                    if (strcmp(unknown_global_packet_a3f640.Name, Unknown_006FA120(unknown_players_a3fa7c[i]->Name)) == 0) {
                        delete unknown_players_a3fa7c[i];
                        unknown_players_a3fa7c.Delete(unknown_players_a3fa7c[i]);
                        break;
                    }
                }
                EnableWindow(Get_Item(window, 0x6D1), FALSE);
                EnableWindow(Get_Item(window, 0x5C0), TRUE);
            } else if (unknown_global_packet_a3f640.Command == 0x25) {
                for (i = 0; i < unknown_session_a3d298.ScoreCount; i++) {
                    if (strcmp(unknown_global_packet_a3f640.Name, Unknown_006FA120(unknown_score_list_850448[i]->Name)) == 0) {
                        int id = unknown_score_controls_7d1498[i][0];
                        wchar_t const *text = StringTable::Load_String("TXT_WAITING", 0, "D:\\Ra2\\CampScor.cpp", 625);
                        HWND item = Get_Item(window, id);
                        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
                        unknown_score_ready_8504c8[i] = false;
                        break;
                    }
                }
            } else if (unknown_global_packet_a3f640.Command == 0x26) {
                unknown_score_850504 = true;
                break;
            } else if (unknown_all_ready_465f80() && more) {
                unknown_score_850504 = true;
                    Send_Score_Packet(0x26);
                break;
            }
        }
        unknown_5159b0(0, true);
        unknown_dialog_5ff6e0(window);
        unknown_5159b0(0, true);
    }
    if (unknown_game_mode_a3d298 == 4) {
        unknown_ipx_manager_a40978.unknown_527800();
    }
    Unknown_Free_Art_Flagged_006F2750();
}
