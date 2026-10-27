// void __fastcall Unknown_006F6BC0(UnknownPointerList *list, UnknownTest test, UnknownVisit visit, int test_argument, int visit_argument) (0x006F6BC0)
// Calls visit(item, visit_argument) for every item of the list for which test(item, test_argument) holds.
#include "shared/uicmnds.hpp"


void __fastcall Unknown_006F6BC0(UnknownPointerList *list, UnknownTest test, UnknownVisit visit, int test_argument, int visit_argument)
{
    int count = list->Count;
    for (int index = 0; index < count; index++) {
        void *item = list->Items[index];
        if (test(item, test_argument)) {
            visit(item, visit_argument);
        }
    }
}
