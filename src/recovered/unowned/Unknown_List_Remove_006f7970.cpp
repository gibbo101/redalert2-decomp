// void __fastcall Unknown_006F7970(void *item) (0x006F7970)
// Removes the last entry equal to item from the list at 0x00AC1344 (searched from the end).
// @ref ?unknown_list_ac1344@@3PAUUnknownPointerList@@A=00ac1344
#include "shared/uicmnds.hpp"

extern UnknownPointerList *unknown_list_ac1344;

void __fastcall Unknown_006F7970(void *item)
{
    if (unknown_list_ac1344 != 0) {
        for (int index = unknown_list_ac1344->Count - 1; index >= 0; index--) {
            if (unknown_list_ac1344->Items[index] == item) {
                unknown_list_ac1344->Delete(index);
                break;
            }
        }
    }
}
