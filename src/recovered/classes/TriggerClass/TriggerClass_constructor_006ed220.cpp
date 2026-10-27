// TriggerClass::TriggerClass(TriggerTypeClass *type) (0x006ED220)
// A live trigger; disabled when its type is, or for the current difficulty.
#include "shared/object.hpp"

// The abstract list 0x00AC0D48 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d48;

TriggerClass::TriggerClass(TriggerTypeClass *type) :
    Class(type),
    Next(0),
    unknown_2c(false),
    Events(0),
    IsEnabled(true)
{
    unknown_objects_ac0cb0.Add((ObjectClass *)this);
    unknown_AbstractClass_list_00ac0d48.Add(this);
    unknown_TriggerClass_list_00a40aa0.Add(this);
    if (Class != 0) {
        Reset();
        if (!Class->IsEnabled || (Scenario_Difficulty() == 0 && !Class->IsEasy) ||
            (Scenario_Difficulty() == 1 && !Class->IsNormal) || (Scenario_Difficulty() == 2 && !Class->IsHard)) {
            IsEnabled = false;
        }
    }
}
