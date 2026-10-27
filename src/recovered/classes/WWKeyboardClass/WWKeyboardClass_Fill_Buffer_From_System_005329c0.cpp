// void WWKeyboardClass::Fill_Buffer_From_System() (0x005329C0)
// Unless the queue is full, lets the window messages add keys.
#include "shared/keyboard.hpp"
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0

void WWKeyboardClass::Fill_Buffer_From_System()
{
    if (!Is_Buffer_Full()) {
        Unknown_005B5EE0();
    }
}
