// HRESULT __stdcall CChatEventSink::OnUpdateList(HRESULT result, WOL::Update *updates) (0x0075EA50, slot 4)
// Offers the required patches; on acceptance downloads each one (showing "x of y" in the download
// dialog), then asks for a restart and signals unknown_b26518. Without patches, on refusal or on a
// cancelled download it signals unknown_b264f8.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/dialog_create.hpp"
#include "shared/wonline_dialog_control.hpp"
// @ref ?unknown_login_state_00b2abe4@@3HA=00b2abe4
// @ref ?unknown_b2abe0@@3IA=00b2abe0
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_007357E0@@YIXPAXH@Z=007357e0
// @ref ?Unknown_0073c120@@YAXXZ=0073c120
// @ref ?unknown_download_a72d04@@3PAUIDownload@WOL@@A=00a72d04
// @ref ?unknown_b26518@@3PAXA=00b26518
// @ref ?unknown_b264f8@@3PAXA=00b264f8
// @ref ?Download_Dialog_Proc_00748cd0@@YGHPAUHWND__@@IIJ@Z=00748cd0
// @ref ??_7SimpleWonlineDialogControl@@6B@=007af6f4
// @ref ??_GSimpleWonlineDialogControl@@UAEPAXI@Z=0075d0a0
// @ref ?unknown_slot4@SimpleWonlineDialogControl@@UAE_NXZ=0073c030
// @ref _sprintf=007820f4

HRESULT __stdcall CChatEventSink::OnUpdateList(HRESULT result, WOL::Update *updates)
{
    int count = 0;
    if (result >= 0 && updates) {
        unknown_login_state_00b2abe4 = 1;
        WOL::Update *update;
        for (update = updates; update; update = update->next) ++count;
        void *list = Unknown_00735940(0xc4);
        if (list) {
            if (!(unknown_b2abe0 &= ~0x10)) Unknown_007357E0(list, 0);
        }
        HWND current = Unknown_00735B10();
        HWND edit = GetDlgItem(current, 0x540);
        if (edit) SetFocus(edit);
        if (Popup_005c3230(StringTable::Load_String("TXT_UPGRADEREQUIRED", 0, "D:\\Ra2\\wonline.cpp", 0x10de), 4, Unknown_0073c120, 0) == 7) {
            SetEvent(unknown_b264f8);
            return S_OK;
        }
        char directory[260];
        GetCurrentDirectoryA(256, directory);
        int index = 0;
        update = updates;
        while (update) {
            char file[260];
            char local[260];
            wchar_t text[200];
            sprintf(file, "%s/%s", update->patchpath, update->patchfile);
            sprintf(local, "%s\\%s", update->localpath, update->patchfile);
            CreateDirectoryA(update->localpath, 0);
            unknown_download_a72d04->DownloadFile(update->server, update->login, update->password, file, local, "SOFTWARE\\Westwood\\Red Alert 2");
            ++index;
            swprintf(text, StringTable::Load_String("TXT_DOWNLOADING_X_OF_Y", 0, "D:\\Ra2\\wonline.cpp", 0x10f4), index, count);
            WideString message(text);
            SimpleWonlineDialogControl control;
            HWND dialog = unknown_create_dialog_5ff610(0xd3, Download_Dialog_Proc_00748cd0, 0);
            HWND item = GetDlgItem(dialog, 0x5c7);
            SendMessageA(item, 0x4b2, 0, (LPARAM)message.unknown_text_770430());
            if (Unknown_007359e0(dialog, (bool (*)())Unknown_0073c120, 0, 1, 1) == 2) {
                SetEvent(unknown_b264f8);
                SetCurrentDirectoryA(directory);
                return S_OK;
            }
            update = update->next;
        }
        Popup_005c3230(StringTable::Load_String("TXT_GAME_RESTART", 0, "D:\\Ra2\\wonline.cpp", 0x1114), 0, Unknown_0073c120, 0);
        SetEvent(unknown_b26518);
        SetCurrentDirectoryA(directory);
        return S_OK;
    }
    SetEvent(unknown_b264f8);
    return S_OK;
}
// @ref ??_C@_0BB@KAHC@TXT_GAME_RESTART?$AA@=007fdca4
// @ref ??_C@_0BE@MMD@TXT_UPGRADEREQUIRED?$AA@=007fdcd8
// @ref ??_C@_0BH@LLDC@TXT_DOWNLOADING_X_OF_Y?$AA@=007fdcb8
// @ref ??_C@_05LELA@?$CFs?1?$CFs?$AA@=007fdcd0
// @ref ??_C@_05KEJO@?$CFs?2?$CFs?$AA@=007f4dd0
// @ref ??_C@_0BO@MFMF@SOFTWARE?2Westwood?2Red?5Alert?52?$AA@=007e6ad8
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
