// void TriggerClass::unknown_func_6ed990() (0x006ED990)
// Marks the trigger and queues it in the abstract list 0x00AC0CD8.
#include "shared/object.hpp"

void TriggerClass::unknown_func_6ed990()
{
    unknown_2c = true;
    unknown_objects_ac0cd8.Add(this);
}
