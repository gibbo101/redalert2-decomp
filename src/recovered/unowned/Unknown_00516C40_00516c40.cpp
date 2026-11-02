// int __stdcall Unknown_00516C40(HWND, UINT, WPARAM, LPARAM) -- 0x00516C40
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/win_stub.hpp"
#include "shared/cpu_info.hpp"
#include "shared/crt_string.hpp"
#include "shared/unknown_globals.hpp"

// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_0BA@GICH@TXT_SHORT_TITLE?$AA@=007d33cc
// @ref ??_C@_0L@DEPB@Version?5?$CFs?$AA@=007dc0c4
// @ref ??_C@_0BE@LINL@Internal?5Version?5?$CFs?$AA@=007dc0b0
// @ref ??_C@_0BN@PIFH@Release?5Build?3?5?$CFs?5by?5?$CFs?5?9?5?$CFs?$AA@=007dc090
// @ref ??_C@_03PEHN@Yes?$AA@=007d7ba4
// @ref ??_C@_02JOHD@No?$AA@=007d7ba0
// @ref ??_C@_0BD@JKIO@MMX?5?$CFs?0?5Vendor?3?5?$CFs?$AA@=007dc07c
// @ref ?version_object_00a40c88@@3VVersionClass@@A=00a40c88
// @ref ?unknown_version_text_7131d0@@YAPBDXZ=007131d0
// @ref ?unknown_internal_version_text_712ed0@@YIPBDPAVVersionClass@@@Z=00712ed0
// @ref ?unknown_build_machine_text_737ad0@@YIPADPADH@Z=00737ad0
// @ref ?unknown_build_user_text_737b00@@YIPADPADH@Z=00737b00
// @ref ?unknown_clear_text_4955a0@@YIXPAD@Z=004955a0
// @ref ?unknown_cpu_text_8015a5@@3PADA=008015a5
// @ref ?unknown_profile_cpu_text_a411fc@@3PADA=00a411fc
// @ref ?unknown_profile_ram_text_a41388@@3PADA=00a41388
// @ref ?unknown_profile_vram_text_a41308@@3PADA=00a41308
// @ref ?unknown_profile_blit_text_a41408@@3PADA=00a41408
// @ref ?unknown_profile_text_a4127c@@3PADA=00a4127c

class VersionClass;
extern VersionClass version_object_00a40c88;
char const *unknown_version_text_7131d0();                                                    // 0x007131D0
char const *__fastcall unknown_internal_version_text_712ed0(VersionClass *object);    // 0x00712ED0
char *__fastcall unknown_build_machine_text_737ad0(char *buffer, int size);                   // 0x00737AD0
char *__fastcall unknown_build_user_text_737b00(char *buffer, int size);                      // 0x00737B00
void __fastcall unknown_clear_text_4955a0(char *text);                                        // 0x004955A0
extern char unknown_cpu_text_8015a5[];

// The version dialog's procedure (pointer only, 0x00516E70's dialog 0xD4): the common handler
// first; 0x497 fills item 0x5B5 with the title, the versions, the build, the system texts and
// the CPU line; WM_COMMAND ids 1 and 2 are stored in the int the window's long 8 points at.
int __stdcall Unknown_00516C40(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    char buffer[256];
    char time[128];
    char machine[128];
    char user[128];
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *choice = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x497:
        {
            HWND item = GetDlgItem(window, 0x5B5);
            SendMessageA(item, 0x4CD, 0, (LPARAM)StringTable::Load_String("TXT_SHORT_TITLE", 0, "D:\\Ra2\\Init.CPP", 5428));
            sprintf(buffer, "Version %s", unknown_version_text_7131d0());
            SendMessageA(item, 0x4C8, 0, (LPARAM)buffer);
            sprintf(buffer, "Internal Version %s", unknown_internal_version_text_712ed0(&version_object_00a40c88));
            SendMessageA(item, 0x4C8, 0, (LPARAM)buffer);
            time[0] = 0;
            Build_Time_Text(time, sizeof(time));
            sprintf(buffer, "Release Build: %s by %s - %s", unknown_build_machine_text_737ad0(machine, sizeof(machine)),
                unknown_build_user_text_737b00(user, sizeof(user)), time);
            SendMessageA(item, 0x4C8, 0, (LPARAM)buffer);
            int family = 5;
            unsigned char mmx = 0;
            SendMessageA(item, 0x4C8, 0, (LPARAM)unknown_profile_cpu_text_a411fc);
            SendMessageA(item, 0x4C8, 0, (LPARAM)unknown_profile_ram_text_a41388);
            SendMessageA(item, 0x4C8, 0, (LPARAM)unknown_profile_vram_text_a41308);
            SendMessageA(item, 0x4C8, 0, (LPARAM)unknown_profile_blit_text_a41408);
            SendMessageA(item, 0x4C8, 0, (LPARAM)unknown_profile_text_a4127c);
            Get_CPU_Info(&family, &mmx, 0, 0);
            sprintf(buffer, "MMX %s, Vendor: %s", mmx ? "Yes" : "No", unknown_cpu_text_8015a5);
            SendMessageA(item, 0x4C8, 0, (LPARAM)buffer);
            unknown_clear_text_4955a0(buffer);
            SendMessageA(item, 0x4C8, 0, (LPARAM)buffer);
        }
        return 0;
    case 0x111:
        if ((int)(wparam & 0xFFFF) > 0 && (int)(wparam & 0xFFFF) <= 2) {
            *choice = wparam & 0xFFFF;
        }
        break;
    }
    return 0;
}
