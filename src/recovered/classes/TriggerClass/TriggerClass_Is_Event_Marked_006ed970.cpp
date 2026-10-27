// bool TriggerClass::Is_Event_Marked(int index) const (0x006ED970)
#include "shared/object.hpp"

bool TriggerClass::Is_Event_Marked(int index) const
{
    return (Events & (1 << index)) != 0;
}
