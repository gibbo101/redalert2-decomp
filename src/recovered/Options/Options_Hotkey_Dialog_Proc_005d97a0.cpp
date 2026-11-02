// int __stdcall Unknown_Options_Dialog_Proc_005d97a0(HWND, UINT, WPARAM, LPARAM) (0x005D97A0)
// The keyboard dialog (0xA3, run by OptionsClass::Unknown_005DA360; TS Hotkey_Dialog_Proc): category
// combo 0x4C7, command list 0x4C8, description 0x4CB, current shortcut 0x63C, hot key control 0x4CD,
// assigned-to 0x63B, error text 0x63D. It posts itself 0x464 (fill the command list), 0x465 (show the
// selected command), 0x466 (assign the hot key) and 0x467 (refill the categories; also sent for 0x497).
// 0x686 writes KEYBOARD.INI ([Hotkey] name = key), Cancel reloads it, 0x4D0 deletes it.
// Needs INDEX_DECLARE_FETCH_ID_BY_POSITION and the vector accessors (defined in the unit's first source,
// Options_Hotkey_To_Key_005d87d0.cpp).
// @ref ?Binary_Search@@YIPAUNodeElement@?$IndexClass@HPAVCommandClass@@@@PAU12@HABU12@@Z=005da590
// @ref _?current_selection@?1??Unknown_Options_Dialog_Proc_005d97a0@@YGHPAUHWND__@@IIJ@Z@4HA=007e8414
// @ref ??_C@_0BA@KKIC@Error?3CannotMap?$AA@=007e8a38
// @ref ??_C@_0BC@MFEG@Error?3CannotRemap?$AA@=007e8a24
// @ref ??_C@_0BN@DILJ@Deleting?5users?5KEYBOARD?4INI?6?$AA@=007e8a5c
// @ref ??_C@_0N@GLNH@Keyboard?4ini?$AA@=007e8a7c
// @ref ??_C@_0BD@LCMK@D?3?2Ra2?2Options?4CPP?$AA@=007e8a48
// @ref ??_C@_06KFPB@Hotkey?$AA@=007dd710
// @ref ??_C@_0N@CJMM@KEYBOARD?4INI?$AA@=007dd718
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ?unknown_hotkeys_832380@@3V?$IndexClass@HPAVCommandClass@@@@A=00832380
// @ref ?unknown_commands_832358@@3V?$DynamicVectorClass@PBVCommandClass@@@@A=00832358
// @ref ?search_compfunc@?$IndexClass@HPAVCommandClass@@@@CAHPBX0@Z=00480c00
// @ref ?x@?1???A?$IndexClass@HPAVCommandClass@@@@QBEABQAVCommandClass@@ABH@Z@4PAV2@A=00b2b63c
// @ref ?Increase_Table_Size@?$IndexClass@HPAVCommandClass@@@@QAE_NH@Z=0051e760
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
#include "shared/options.hpp"
#include "shared/command.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/debug_printf.hpp"
#include "shared/string_table.hpp"
#include "shared/dialog_default_proc.hpp"
#include "shared/owner_draw_dialog_control.hpp"

bool __fastcall Load_Keyboard_Hotkeys();
bool __fastcall Command_Allows_Modified_Key_00480b20(CommandClass const &command, unsigned int key);
bool __fastcall Command_Allows_Key_00480b40(unsigned int key);
extern "C" int __cdecl _wcsicmp(wchar_t const *left, wchar_t const *right);

int __stdcall Unknown_Options_Dialog_Proc_005d97a0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    wchar_t buffer[64];
    int *retval;
    static int current_selection = -1;

    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) {
        return result;
    }

    retval = (int *)GetWindowLongA(window, 8);

    switch (message) {
        case 0x466: {
            HWND list_commands = GetDlgItem(window, 0x4C8);
            int selection = SendMessageA(list_commands, 0x188, 0, 0);
            if (selection != -1) {
                CommandClass *cmd = (CommandClass *)SendMessageA(list_commands, 0x199, selection, 0);
                HWND hotkey = GetDlgItem(window, 0x4CD);
                int key = Hotkey_To_Key(SendMessageA(hotkey, 0x402, 0, 0));
                if (!Command_Allows_Modified_Key_00480b20(*cmd, key)) {
                    HWND error = GetDlgItem(window, 0x63D);
                    SendMessageA(error, 0x4B2, 0, (LPARAM)StringTable::Load_String("Error:CannotMap", 0, "D:\\Ra2\\Options.CPP", 987));
                } else if (!Command_Allows_Key_00480b40(key)) {
                    HWND error = GetDlgItem(window, 0x63D);
                    SendMessageA(error, 0x4B2, 0, (LPARAM)StringTable::Load_String("Error:CannotRemap", 0, "D:\\Ra2\\Options.CPP", 995));
                    return TRUE;
                } else {
                    for (int i = 0; i < unknown_hotkeys_832380.Count(); i++) {
                        if (unknown_hotkeys_832380.Fetch_By_Position(i) == cmd) {
                            unknown_hotkeys_832380.Remove_Index(unknown_hotkeys_832380.Fetch_ID_By_Position(i));
                            break;
                        }
                    }
                    if (key != 0) {
                        unknown_hotkeys_832380.Remove_Index(key);
                        unknown_hotkeys_832380.Add_Index(key, cmd);
                        return TRUE;
                    }
                }
            }
            return TRUE;
        }

        case 0x465: {
            HWND list_commands = GetDlgItem(window, 0x4C8);
            int selection = SendMessageA(list_commands, 0x188, 0, 0);
            if (selection != -1) {
                CommandClass const *cmd = (CommandClass const *)SendMessageA(list_commands, 0x199, selection, 0);
                HWND description = GetDlgItem(window, 0x4CB);
                SendMessageA(description, 0x4B2, 0, (LPARAM)cmd->Get_Description());

                int key = 0;
                for (int i = 0; i < unknown_hotkeys_832380.Count(); i++) {
                    if (unknown_hotkeys_832380.Fetch_By_Position(i) == cmd) {
                        key = unknown_hotkeys_832380.Fetch_ID_By_Position(i);
                        break;
                    }
                }

                HWND key_label = GetDlgItem(window, 0x63C);
                OwnerDraw::unknown_hotkey_text_5fc600(Key_To_Hotkey(key), buffer);
                SendMessageA(key_label, 0x4B2, 0, (LPARAM)buffer);

                HWND hotkey = GetDlgItem(window, 0x4CD);
                SendMessageA(hotkey, 0x401, 0, 0);

                HWND hotkey_name = GetDlgItem(window, 0x63B);
                SendMessageA(hotkey_name, 0x4B2, 0, (LPARAM)L"");
                return TRUE;
            }
            return TRUE;
        }

        case 0x464: {
            HWND cmb_category = GetDlgItem(window, 0x4C7);
            if (SendMessageA(cmb_category, 0x147, 0, 0) != current_selection) {
                current_selection = SendMessageA(cmb_category, 0x147, 0, 0);
                SendMessageA(cmb_category, 0x4B3, 64, (LPARAM)buffer);
                HWND list_commands = GetDlgItem(window, 0x4C8);
                SendMessageA(list_commands, 0x184, 0, 0);
                for (int i = 0; i < unknown_commands_832358.Count(); i++) {
                    CommandClass const *cmd = unknown_commands_832358[i];
                    if (_wcsicmp(cmd->Get_Category(), buffer) == 0) {
                        int index = SendMessageA(list_commands, 0x4CD, 0, (LPARAM)cmd->Get_UI_Name());
                        if (index != -1) {
                            SendMessageA(list_commands, 0x19A, index, (LPARAM)cmd);
                        }
                    }
                }
                HWND description = GetDlgItem(window, 0x4CB);
                SendMessageA(description, 0x4B2, 0, (LPARAM)L"");
                HWND key_label = GetDlgItem(window, 0x63C);
                SendMessageA(key_label, 0x4B2, 0, (LPARAM)L"");
                HWND hotkey_name = GetDlgItem(window, 0x63B);
                SendMessageA(hotkey_name, 0x4B2, 0, (LPARAM)L"");
                SendMessageA(hotkey_name, 0x186, 0, 0);
                SendMessageA(window, 0x465, 0, 0);
                return TRUE;
            }
            return TRUE;
        }

        case 0x467: {
            HWND cmb_category = GetDlgItem(window, 0x4C7);
            SendMessageA(cmb_category, 0x14B, 0, 0);
            for (int i = 0; i < unknown_commands_832358.Count(); i++) {
                CommandClass const *cmd = unknown_commands_832358[i];
                if (SendMessageA(cmb_category, 0x4BE, 0, (LPARAM)cmd->Get_Category()) == -1) {
                    SendMessageA(cmb_category, 0x4C2, 0, (LPARAM)cmd->Get_Category());
                }
            }
            SendMessageA(cmb_category, 0x14E, 0, 0);
            current_selection = -1;
            SendMessageA(window, 0x464, 0, 0);
            return TRUE;
        }

        case 0x497:
            SendMessageA(window, 0x467, 0, 0);
            return FALSE;
        case 0x111:
            switch ((unsigned short)wparam) {
                case 0x686:
                    if ((unsigned short)(wparam >> 16) == 0) {
                        CCINIClass ini;
                        ini.Clear();
                        for (int i = 0; i < unknown_hotkeys_832380.Count(); i++) {
                            CommandClass const *cmd = unknown_hotkeys_832380.Fetch_By_Position(i);
                            int key = unknown_hotkeys_832380.Fetch_ID_By_Position(i);
                            ini.Put_Int("Hotkey", cmd->Get_Name(), key);
                        }
                        RawFileClass file("Keyboard.ini");
                        ini.Save(file, false);
                        *retval = 1;
                        return TRUE;
                    }
                    break;

                case 2:
                    if ((unsigned short)(wparam >> 16) == 0) {
                        Load_Keyboard_Hotkeys();
                        *retval = 2;
                        return TRUE;
                    }
                    break;

                case 0x4C8:
                    if ((unsigned short)(wparam >> 16) == 1) {
                        SendMessageA(window, 0x465, 0, 0);
                        HWND hotkey = GetDlgItem(window, 0x4CD);
                        if (hotkey != 0) {
                            SetFocus(hotkey);
                            return TRUE;
                        }
                    }
                    break;

                case 0x4CF:
                    SendMessageA(window, 0x466, 0, 0);
                    SendMessageA(window, 0x465, 0, 0);
                    return TRUE;

                case 0x4CD:
                    if ((unsigned short)(wparam >> 16) == 0x300) {
                        HWND error = GetDlgItem(window, 0x63D);
                        SendMessageA(error, 0x4B2, 0, (LPARAM)L"");
                        int key = Hotkey_To_Key(SendMessageA((HWND)lparam, 0x402, 0, 0));
                        wchar_t const *key_name;
                        if (unknown_hotkeys_832380.Is_Present(key)) {
                            key_name = unknown_hotkeys_832380[key]->Get_UI_Name();
                            if (key_name == 0) {
                                key_name = L"";
                            }
                        } else {
                            key_name = L"";
                        }
                        HWND hotkey_name = GetDlgItem(window, 0x63B);
                        SendMessageA(hotkey_name, 0x4B2, 0, (LPARAM)key_name);
                        return TRUE;
                    }
                    break;

                case 0x4D0:
                    if ((unsigned short)(wparam >> 16) == 0) {
                        Debug_Printf("Deleting users KEYBOARD.INI\n");
                        CCFileClass file("KEYBOARD.INI");
                        file.Delete();
                        Load_Keyboard_Hotkeys();
                        SendMessageA(window, 0x467, 0, 0);
                        return TRUE;
                    }
                    break;

                case 0x4C7:
                    if ((unsigned short)(wparam >> 16) == 1) {
                        SendMessageA(window, 0x464, 0, 0);
                        return TRUE;
                    }
                    break;
            }
            return TRUE;

    }

    return FALSE;
}
