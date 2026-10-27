// bool WWKeyboardClass::Put_Element(KeyNumType key) (0x00532940)
// Appends an element; false when the queue is full.
#include "shared/keyboard.hpp"

bool WWKeyboardClass::Put_Element(KeyNumType key)
{
    if (!Is_Buffer_Full()) {
        int next = (Tail + 1) % 256;
        Buffer[Tail] = key;
        Tail = next;
        return true;
    }
    return false;
}
