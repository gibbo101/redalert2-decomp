// void WWKeyboardClass::Clear() (0x005329F0)
// Discards everything queued, including keys the pending window messages add.
#include "shared/keyboard.hpp"
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0

void WWKeyboardClass::Clear()
{
    Fill_Buffer_From_System();
    Head = Tail;
    Fill_Buffer_From_System();
    Head = Tail;
}
