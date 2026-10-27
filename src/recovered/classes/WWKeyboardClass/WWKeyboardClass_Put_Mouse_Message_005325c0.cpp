// bool WWKeyboardClass::Put_Mouse_Message(KeyNumType key, int x, int y, bool release) (0x005325C0)
// Queues a mouse key and its position when three slots are free.
#include "shared/keyboard.hpp"
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?Put_Key_Message@WWKeyboardClass@@QAE_NG_N@Z=005324d0

bool WWKeyboardClass::Put_Mouse_Message(KeyNumType key, int x, int y, bool release)
{
    if (unknown_flag_a40d44) {
        return true;
    }
    if (Available() >= 3 && Is_Mouse_Key(key)) {
        Put_Key_Message(key, release);
        Put((KeyNumType)x);
        Put((KeyNumType)y);
        return true;
    }
    return false;
}
