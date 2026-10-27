// bool WWKeyboardClass::Put_Key_Message(KeyNumType key, bool release) (0x005324D0)
// Records the key state, adds the shift/control/alt bits of a keyboard key
// and the release bit, and queues it. Alt+tab is dropped; while the keyboard
// is ignored only VK_ESCAPE gets through.
#include "shared/keyboard.hpp"
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?Unknown_005233A0@@YIXH_N@Z=005233a0
// @ref ?Unknown_005233D0@@YIFH@Z=005233d0

bool WWKeyboardClass::Put_Key_Message(KeyNumType key, bool release)
{
    if (unknown_flag_a40d44 && key != 0x1B) {
        return true;
    }
    Unknown_005233A0(key, release);
    if (!Is_Mouse_Key(key) && !Is_Char_Key(key)) {
        if ((Unknown_005233D0(0x10) & 0x8000) != 0) {
            key |= 0x100;
        }
        if ((Unknown_005233D0(0x11) & 0x8000) != 0) {
            key |= 0x200;
        }
        if ((Unknown_005233D0(0x12) & 0x8000) != 0) {
            if (key == 0x09) {
                return true;
            }
            key |= 0x400;
        }
    }
    if (release) {
        key |= 0x800;
    }
    return Put(key);
}
