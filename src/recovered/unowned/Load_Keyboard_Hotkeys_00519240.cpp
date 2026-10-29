// bool __fastcall Load_Keyboard_Hotkeys() -- 0x00519240
// __fastcall (no parameters): as __cdecl VC6 schedules the object address loads after the argument pushes.
// Body 0x00519240-0x00519471 (562 bytes; the inventory's 552 stops before the failure path's epilogue).
#include "shared/command.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/debug_printf.hpp"

// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ?unknown_commands_832358@@3V?$DynamicVectorClass@PBVCommandClass@@@@A=00832358
// @ref ?unknown_hotkeys_832380@@3V?$IndexClass@HPAVCommandClass@@@@A=00832380
// @ref ?Increase_Table_Size@?$IndexClass@HPAVCommandClass@@@@QAE_NH@Z=0051e760
// @ref ??_C@_0N@CJMM@KEYBOARD?4INI?$AA@=007dd718
// @ref ??_C@_06KFPB@Hotkey?$AA@=007dd710
// @ref ??_C@_0BN@BGIA@Unable?5to?5load?5KEYBOARD?4INI?6?$AA@=007dd6f0

extern "C" int __cdecl strcmp(char const *left, char const *right);

// Reads the [Hotkey] section of KEYBOARD.INI (command name = key) into the hotkey table,
// replacing it; false when the file cannot be read.
bool __fastcall Load_Keyboard_Hotkeys()
{
    CCINIClass ini;
    CCFileClass file("KEYBOARD.INI");
    if (ini.Load(file, false, false)) {
        unknown_hotkeys_832380.Clear();
        for (int index = 0; index < ini.Entry_Count("Hotkey"); index++) {
            char const *entry = ini.Get_Entry("Hotkey", index);
            int key = ini.Get_Int("Hotkey", entry, 0);
            for (int command = 0; command < unknown_commands_832358.Count(); command++) {
                if (strcmp(unknown_commands_832358[command]->Get_Name(), entry) == 0) {
                    CommandClass *found = (CommandClass *)unknown_commands_832358[command];
                    if (found != 0 && key != 0) {
                        unknown_hotkeys_832380.Add_Index(key, found);
                    }
                    break;
                }
            }
    }
    return true;
    }
    Debug_Printf("Unable to load KEYBOARD.INI\n");
    return false;
}
