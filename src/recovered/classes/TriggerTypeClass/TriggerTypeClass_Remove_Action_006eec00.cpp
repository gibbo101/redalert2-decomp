// bool TriggerTypeClass::Remove_Action(TActionClass *action) (0x006EEC00)
// Unlinks and deletes an action of the type.
#include "shared/object.hpp"

bool TriggerTypeClass::Remove_Action(TActionClass *action)
{
    TActionClass *current = Actions;
    if (current == action) {
        Actions = action->Next;
        delete action;
        return true;
    }
    while (current != 0) {
        if (current->Next == action) {
            current->Next = current->Next->Next;
            delete action;
            return true;
        }
        current = current->Next;
    }
    return false;
}
