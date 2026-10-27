// void TriggerClass::unknown_func_6ed650(int value) (0x006ED650)
// Resets every trigger of the chain (from this one) whose type answers
// TriggerTypeClass::unknown_func_6ee280(value).
#include "shared/object.hpp"

void TriggerClass::unknown_func_6ed650(int value)
{
    for (TriggerClass *trigger = this; trigger != 0; trigger = trigger->Next) {
        if (trigger->Class->unknown_func_6ee280(value)) {
            trigger->Reset();
        }
    }
}
