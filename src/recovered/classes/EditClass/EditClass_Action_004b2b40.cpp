#include "shared/gadget.hpp"
#include "shared/keyboard.hpp"
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?To_ASCII@WWKeyboardClass@@QAEDG@Z=00532720
// @ref ?Action@ControlClass@@UAEHIAAI@Z=004834b0
int EditClass::Action(unsigned flags, unsigned &key)
{
    if (IsReadOnly) return 0;
    if (flags & LEFTPRESS) {
        flags &= ~LEFTPRESS;
        Set_Focus();
        Flag_To_Redraw();
    }
    if ((flags & KEYBOARD) && Has_Focus()) {
        unsigned current_key = key;
        if (current_key == 27) {
            Clear_Focus();
            flags = 0;
            goto done;
        }
        int ascii = (unsigned char)WWKeyboard->To_ASCII((KeyNumType)current_key);
        current_key = key;
        if ((current_key & 0x1000) && ascii >= '0' && ascii <= '9') {
            key &= ~0x1000;
            if (flags & 0x44) goto done;
            if (!Handle_Key(ascii)) goto done;
        } else {
            if (((current_key & 0x1000) == 0 && ascii >= 32 && ascii <= 255) || current_key == 13 || current_key == 8) {
                if (flags & 0x44) goto done;
                if (!Handle_Key(WWKeyboard->To_ASCII((KeyNumType)current_key))) goto done;
            }
        }
        flags &= ~KEYBOARD;
        key = 0;
    }
done:
    return ControlClass::Action(flags, key);
}
