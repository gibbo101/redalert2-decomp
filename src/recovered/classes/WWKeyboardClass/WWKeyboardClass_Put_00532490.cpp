// bool WWKeyboardClass::Put(KeyNumType key) (0x00532490)
// Queues a key; false when the queue is full.
#include "shared/keyboard.hpp"

bool WWKeyboardClass::Put(KeyNumType key)
{
    if (!Is_Buffer_Full()) {
        Put_Element(key);
        return true;
    }
    return false;
}
