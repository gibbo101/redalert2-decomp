// KeyNumType WWKeyboardClass::Check() (0x005322D0)
// Lets the window messages fill the queue, then returns the next key without
// removing it, or 0.
#include "shared/keyboard.hpp"
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0

KeyNumType WWKeyboardClass::Check()
{
    Fill_Buffer_From_System();
    if (Is_Buffer_Empty()) {
        return 0;
    }
    return Peek_Element();
}
