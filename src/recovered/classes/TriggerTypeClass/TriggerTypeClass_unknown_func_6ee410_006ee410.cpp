// int TriggerTypeClass::unknown_func_6ee410() const (0x006EE410)
// The combined flags of the events and actions of this and the later types.
#include "shared/object.hpp"

int TriggerTypeClass::unknown_func_6ee410() const
{
    int flags = 0;
    for (TEventClass *event = Events; event != 0; event = event->Next) {
        flags |= TEventClass::Event_Flags(event->Type);
    }
    for (TActionClass *action = Actions; action != 0; action = action->Next) {
        flags |= TActionClass::Action_Flags(action->Type);
    }
    if (Next != 0) {
        return Next->unknown_func_6ee410() | flags;
    }
    return flags;
}
