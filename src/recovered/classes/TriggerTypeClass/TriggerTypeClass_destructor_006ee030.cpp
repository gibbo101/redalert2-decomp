// TriggerTypeClass::~TriggerTypeClass() (0x006EE030)
// Detaches the type, leaves TriggerTypes, deletes its actions and events and
// leaves the abstract lists.
// @ref ?unknown_AbstractClass_list_00ac0c98@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c98
#include "shared/object.hpp"
#include "shared/trigger_type.hpp"
#include "shared/taction.hpp"

TriggerTypeClass::~TriggerTypeClass()
{
    Unknown_006ECB90(this, true);
    TriggerTypes.Delete(this);
    TActionClass *action = Actions;
    while (action != 0) {
        TActionClass *next = action->Next;
        delete action;
        action = next;
    }
    TEventClass *event = Events;
    while (event != 0) {
        TEventClass *next = event->Next;
        delete event;
        event = next;
    }
    unknown_objects_ac0cb0.Delete(this);
    unknown_AbstractClass_list_00ac0c98.Delete(this);
}
