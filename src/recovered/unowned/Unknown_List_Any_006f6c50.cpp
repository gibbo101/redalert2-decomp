// bool __fastcall Unknown_006F6C50(UnknownPointerList *list, UnknownTest test, int argument) (0x006F6C50)
// True when test(item, argument) holds for some item of the list (stops at the first that does).
#include "shared/uicmnds.hpp"


bool __fastcall Unknown_006F6C50(UnknownPointerList *list, UnknownTest test, int argument)
{
    int count = list->Count;
    for (int index = 0; index < count; index++) {
        if (test(list->Items[index], argument)) {
            return true;
        }
    }
    return false;
}
