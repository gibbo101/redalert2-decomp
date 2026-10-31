// void __fastcall Keyboard_Process(int &input) (0x005406E0; Red Alert's Keyboard_Process)
// Passes the key to Message_Input, then runs the hotkey command bound to it
// (modifier bits stripped first, then with them); without one, Escape queues the
// options event, Tab works the sidebar and the arrow keys set or clear the scroll bits.
#include "shared/main_loop.hpp"
#include "shared/queue.hpp"
#include "shared/command.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_view.hpp"
#include "shared/ipx_manager.hpp"
// @ref ?unknown_hotkeys_832380@@=00832380
// @ref ?search_compfunc@?$IndexClass@HPAVCommandClass@@@@=00480c00
// @ref ?x@?1???A?$IndexClass@HPAVCommandClass@@@@QBEABQAVCommandClass@@ABH@Z@4PAV2@A=00b2b63c
// @ref ?unknown_scroll_keys_a6ebdc@@3HA=00a6ebdc
// @ref ?Sidebar_Tab_Key_006818b0@@YIXPAVSidebarClass@@@Z=006818b0
// @ref ?Message_Input@@YIXAAH@Z=00540c20
// @ref ??_C@_1M@GFFL@?$AAD?$AAe?$AAb?$AAu?$AAg?$AA?$AA@=007dd4ac

void __fastcall Keyboard_Process(int &input)
{
    Message_Input(input);
    if (input == 0) {
        return;
    }
    unsigned int plain = input & ~0x800;
    unsigned int key = plain & 0xffffe8ff;
    CommandClass *command = unknown_hotkeys_832380[(int)key];
    if (command == 0) {
        command = unknown_hotkeys_832380[(int)plain];
    } else if (!command->unknown_slot5(plain)) {
        command = unknown_hotkeys_832380[(int)plain];
    }
    if (command != 0 && (!unknown_flag_a40d44 || _wcsicmp(command->Get_Category(), L"Debug") == 0)) {
        if (command->unknown_slot6(input)) {
            command->Execute(input);
        }
        if (command->unknown_slot7(input)) {
            int count = 0;
            int next = Main_Loop_Keyboard()->Check() & 0xffff;
            while (next == input) {
                Main_Loop_Keyboard()->Get();
                next = Main_Loop_Keyboard()->Check() & 0xffff;
                count++;
                if (count >= 10) {
                    break;
                }
            }
        }
        return;
    }
    if (key == 0x1B) {
        Queue_Options();
        return;
    }
    if (key == 9) {
        Sidebar_Tab_Key_006818b0(&Map);
        return;
    }
    if (key == 0x25) {
        if (input & 0x800) {
            unknown_scroll_keys_a6ebdc &= ~0x100;
        } else {
            unknown_scroll_keys_a6ebdc |= 0x100;
        }
        return;
    }
    if (key == 0x27) {
        if (input & 0x800) {
            unknown_scroll_keys_a6ebdc &= ~0x1000;
        } else {
            unknown_scroll_keys_a6ebdc |= 0x1000;
        }
        return;
    }
    if (key == 0x26) {
        if (input & 0x800) {
            unknown_scroll_keys_a6ebdc &= ~0x01;
        } else {
            unknown_scroll_keys_a6ebdc |= 0x01;
        }
        return;
    }
    if (key == 0x28) {
        if (input & 0x800) {
            unknown_scroll_keys_a6ebdc &= ~0x10;
        } else {
            unknown_scroll_keys_a6ebdc |= 0x10;
        }
    }
}
