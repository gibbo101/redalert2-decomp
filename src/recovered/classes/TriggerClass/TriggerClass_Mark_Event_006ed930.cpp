// void TriggerClass::Mark_Event(int index) (0x006ED930)
#include "shared/object.hpp"

void TriggerClass::Mark_Event(int index)
{
    Events |= 1 << index;
}
