// void TriggerTypeClass::Detach(AbstractClass *target, bool all) (0x006EE2C0)
// Passes the detach on to the actions and events, then unlinks target.
#include "shared/object.hpp"

void TriggerTypeClass::Detach(AbstractClass *target, bool all)
{
    if (Next != 0 && (AbstractClass *)Next == target) {
        Next = Next->Next;
    }
    for (TActionClass *action = Actions; action != 0; action = action->Next) {
        action->Detach(target, true);
    }
    if ((AbstractClass *)Actions == target) {
        Actions = Actions->Next;
    }
    for (TEventClass *event = Events; event != 0; event = event->Next) {
        event->Detach(target, true);
    }
    if ((AbstractClass *)Events == target) {
        Events = Events->Next;
    }
}
