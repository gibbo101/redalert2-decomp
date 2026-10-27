// void TriggerClass::Clear_Event(int index) (0x006ED950)
#include "shared/object.hpp"

void TriggerClass::Clear_Event(int index)
{
    Events &= ~(1 << index);
}
