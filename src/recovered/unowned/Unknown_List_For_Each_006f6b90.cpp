// void __fastcall Unknown_006F6B90(UnknownPointerList *list, UnknownVisit visit, int argument) (0x006F6B90)
// Calls visit(item, argument) for every item of the list.
#include "shared/uicmnds.hpp"


void __fastcall Unknown_006F6B90(UnknownPointerList *list, UnknownVisit visit, int argument)
{
    int count = list->Count;
    for (int index = 0; index < count; index++) {
        visit(list->Items[index], argument);
    }
}
