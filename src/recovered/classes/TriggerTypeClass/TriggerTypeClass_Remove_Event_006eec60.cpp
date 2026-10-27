// bool TriggerTypeClass::Remove_Event(TEventClass *event) (0x006EEC60)
// Unlinks and deletes an event of the type.
#include "shared/object.hpp"

bool TriggerTypeClass::Remove_Event(TEventClass *event)
{
    TEventClass *current = Events;
    if (current == event) {
        Events = event->Next;
        delete event;
        return true;
    }
    while (current != 0) {
        if (current->Next == event) {
            current->Next = current->Next->Next;
            delete event;
            return true;
        }
        current = current->Next;
    }
    return false;
}
