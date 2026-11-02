// bool LoadOptionsClass::Dialog() (0x0053B770)
// Runs the load (style 1), save (2) or delete (3) dialog until the player picks a game or leaves.
#include "shared/load_dlg.hpp"
#include "shared/dialog_create.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/cd.hpp"
#include "shared/campaign.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/session_state.hpp"
#include "shared/win_util.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
// @ref ??_C@_0BD@BKAO@D?3?2Ra2?2LoadDlg?4CPP?$AA@=007dfaa4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_07EALP@TXT_YES?$AA@=007dfa5c
// @ref ??_C@_06LMML@TXT_NO?$AA@=007dfa64
// @ref ??_C@_0O@BGCN@SAVE?$CF04lX?4?$CF3s?$AA@=007dfa30
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ?Query_Free_Disk_Kilobytes_00482c80@@YAIXZ=00482c80
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?RequiredCD@CD@@2HA=007d20e0
// @ref ??_7CD@@6B@=0079d868
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref _wcslen=00783605
// @ref _swprintf=00783764
// @ref _wcscpy=00783689
// @ref ??_C@_0BB@FHFL@TXT_CONFIRM_SAVE?$AA@=007dfa1c
// @ref ??_C@_0BG@DIGG@TXT_DELETE_FILE_QUERY?$AA@=007dfa7c
// @ref ??_C@_0BG@IFCN@TXT_ERROR_SAVING_GAME?$AA@=007dfa04
// @ref ??_C@_0BH@EGCB@TXT_ERROR_LOADING_GAME?$AA@=007df9ec
// @ref ??_C@_0BK@PPCE@TXT_MUSTENTER_DESCRIPTION?$AA@=007dfa40
// @ref ??_C@_0N@PHD@TXT_DISKFULL?$AA@=007dfa94
// @ref ??_C@_1O@NHGA@?$AA?$CF?$AAs?$AA?6?$AA?6?$AA?$CF?$AAs?$AA?$AA@=007dfa6c

unsigned int Query_Free_Disk_Kilobytes_00482c80();

bool LoadOptionsClass::Dialog()
{
    HWND dialog = 0;
    HWND list = 0;
    wchar_t buffer[256];
    char filename_buffer[256];

    switch (unknown_04) {
    case 1: {
        dialog = unknown_create_dialog_5ff610(0xb7, (DialogProc)Load_Dialog_Proc, 0);
        list = GetDlgItem(dialog, 0x525);
        HWND title = GetDlgItem(dialog, 0x694);
        SendMessageA(title, 0x4b2, 0, (LPARAM)Load_Menu_Name());
        if (!unknown_session_a3d298.Unknown_00672F10()) {
            HWND button = GetDlgItem(dialog, 0x40c);
            ShowWindow(button, 0);
        }
        break;
    }
    case 2: {
        if (Query_Free_Disk_Kilobytes_00482c80() < (unsigned int)unknown_10) {
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_DISKFULL", 0, "D:\\Ra2\\LoadDlg.CPP", 0x1ad),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\LoadDlg.CPP", 0x1ad), 0, 0, false);
            return false;
        }
        dialog = unknown_create_dialog_5ff610(0x2b4, (DialogProc)Save_Dialog_Proc, 0);
        list = GetDlgItem(dialog, 0x527);
        wchar_t *description = Description;
        HWND edit = GetDlgItem(dialog, 0x526);
        SendMessageA(edit, 0x4b2, 0, (LPARAM)description);
        HWND title = GetDlgItem(dialog, 0x694);
        SendMessageA(title, 0x4b2, 0, (LPARAM)Save_Menu_Name());
        if (!unknown_session_a3d298.Unknown_00672F10()) {
            HWND button = GetDlgItem(dialog, 0x40c);
            ShowWindow(button, 0);
        }
        break;
    }
    case 3: {
        dialog = unknown_create_dialog_5ff610(0x2b5, (DialogProc)Delete_Dialog_Proc, 0);
        list = GetDlgItem(dialog, 0x528);
        HWND title = GetDlgItem(dialog, 0x694);
        SendMessageA(title, 0x4b2, 0, (LPARAM)Delete_Menu_Name());
        if (!unknown_session_a3d298.Unknown_00672F10()) {
            HWND button = GetDlgItem(dialog, 0x40c);
            ShowWindow(button, 0);
        }
        break;
    }
    }

    State = -1;
    if (dialog) {
        SetWindowLongA(dialog, 8, (LONG)this);
        if (list != 0) {
            Fill_List_0053c040(list);
            EnableWindow(GetDlgItem(dialog, 1), bool(SendMessageA(list, 0x18b, 0, 0) > 0));
        }
        unknown_dialog_5ff7c0(dialog);

        do {
            while (State == -1) {
                if (unknown_6000d0() == true) {
                    State = 2;
                }
                if (unknown_14) {
                    ((void (*)())unknown_14)();
                }
                if (!unknown_flag_a40958) {
                    unknown_517370(false);
                }
            }
            if (State == 1 || State == 0x40f) {
                int row = SendMessageA(list, 0x188, 0, 0);
                if (row == -1) {
                    State = -1;
                } else {
                    FileEntryClass *entry = (FileEntryClass *)SendMessageA(list, 0x199, row, 0);
                    switch (unknown_04) {
                    case 1:
                        if (!entry->NeedsDescription) {
                            int old_disk = Unknown_0046E4C0(0x3c);
                            CD::Set_Required_CD(entry->unknown_1a8 == -1 ? -1 : Campaigns[entry->unknown_1a8]->unknown_98);
                            if (!CD().Force_Available(CD::RequiredCD)) {
                                CD::Set_Required_CD(old_disk);
                                State = -1;
                            } else {
                                ShowWindow(dialog, 0);
                                WWMouse->Hide_Mouse();
                                if (!Load(entry->Filename)) {
                                    WWMouse->Show_Mouse();
                                    ShowWindow(dialog, 5);
                                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_LOADING_GAME", 0, "D:\\Ra2\\LoadDlg.CPP", 0x218),
                                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\LoadDlg.CPP", 0x218), 0, 0, false);
                                    ShowWindow(dialog, 0);
                                    State = -1;
                                }
                            }
                        }
                        break;
                    case 2: {
                        HWND item = GetDlgItem(dialog, 0x527);
                        HWND disabled = 0;
                        if (item) {
                            disabled = (HWND)SendMessageA(item, 0x4ef, 0, 0);
                            if (disabled) {
                                OwnerDraw::unknown_5e46c0(disabled, true);
                            }
                        }
                        HWND edit = GetDlgItem(dialog, 0x526);
                        SendMessageA(edit, 0x4b3, 0x50, (LPARAM)buffer);
                        wcstrim(buffer);
                        if (wcslen(buffer) == 0) {
                            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_MUSTENTER_DESCRIPTION", 0, "D:\\Ra2\\LoadDlg.CPP", 0x230),
                                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\LoadDlg.CPP", 0x230), 0, 0, false);
                            SetFocus(GetDlgItem(dialog, 0x526));
                            SendMessageA(GetDlgItem(dialog, 0x526), 0xb1, -1, -1);
                            State = -1;
                            break;
                        }
                        char const *filename = 0;
                        if (entry && entry->HasDescription) {
                            filename = entry->Filename;
                        } else {
                            {
                                CCFileClass file;
                                do {
                                    sprintf(filename_buffer, "SAVE%04lX.%3s", rand(), Extension);
                                    file.Set_Name(filename_buffer);
                                } while (file.Is_Available() == true);
                            }
                            filename = filename_buffer;
                        }
                        if (filename) {
                            bool exists = RawFileClass(filename).Is_Available() == true;
                            if (exists && WWMessageBox(L" ").Process(StringTable::Load_String("TXT_CONFIRM_SAVE", 0, "D:\\Ra2\\LoadDlg.CPP", 0x244),
                                    StringTable::Load_String("TXT_YES", 0, "D:\\Ra2\\LoadDlg.CPP", 0x244),
                                    StringTable::Load_String("TXT_NO", 0, "D:\\Ra2\\LoadDlg.CPP", 0x244), 0, false)) {
                                State = -1;
                            } else {
                                ShowWindow(dialog, 0);
                                if (!Save(filename, buffer)) {
                                    ShowWindow(dialog, 5);
                                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_SAVING_GAME", 0, "D:\\Ra2\\LoadDlg.CPP", 0x253),
                                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\LoadDlg.CPP", 0x253), 0, 0, false);
                                    State = -1;
                                } else {
                                    ShowWindow(dialog, 5);
                                    OwnerDraw::unknown_5e6330(dialog);
                                    wchar_t const *message = Saved_Message();
                                    WWMessageBox(L" ").Process(message,
                                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\LoadDlg.CPP", 0x25b), 0, 0, false);
                                    OwnerDraw::unknown_5e62d0(dialog);
                                    ShowWindow(dialog, 0);
                                    if (Description) {
                                        wcscpy(buffer, Description);
                                    }
                                }
                            }
                        }
                        if (disabled) {
                            OwnerDraw::unknown_5e46c0(disabled, false);
                        }
                        break;
                    }
                    case 3: {
                        swprintf(buffer, L"%s\n\n%s",
                            StringTable::Load_String("TXT_DELETE_FILE_QUERY", 0, "D:\\Ra2\\LoadDlg.CPP", 0x26d), entry->Description);
                        HWND item = GetDlgItem(dialog, 0x528);
                        HWND disabled = 0;
                        if (item) {
                            disabled = (HWND)SendMessageA(item, 0x4ef, 0, 0);
                            if (disabled) {
                                OwnerDraw::unknown_5e46c0(disabled, true);
                            }
                        }
                        if (!WWMessageBox(L" ").Process(buffer,
                                StringTable::Load_String("TXT_YES", 0, "D:\\Ra2\\LoadDlg.CPP", 0x278),
                                StringTable::Load_String("TXT_NO", 0, "D:\\Ra2\\LoadDlg.CPP", 0x278), 0, false)) {
                            Delete_File(entry->Filename);
                            SendMessageA(list, 0x182, row, 0);
                            SendMessageA(list, 0x186, 0, 0);
                            if (SendMessageA(list, 0x18b, 0, 0) > 0) {
                                State = -1;
                            }
                        } else {
                            State = -1;
                        }
                        if (disabled) {
                            OwnerDraw::unknown_5e46c0(disabled, false);
                        }
                        break;
                    }
                    }
                }
            }
        } while (State == -1);
        for (int i = 0; i < Files.Count(); ++i) {
            delete Files[i];
        }
        Files.Clear();
        unknown_dialog_5ff6e0(dialog);
    }
    return State == 0x40f ? true : false;
}
