// void *__fastcall Audio_Find_Listed(int rows) -- 0x00404E00
// Purpose: returns the object (the list node minus 0xA4) on the first
// non-empty list among the first rows of Audio_Priority_Lists, 0 if all are
// empty. What the lists hold is not known yet.
#include "shared/audio_event.hpp"

void *__fastcall Audio_Find_Listed(int rows)
{
    AudioListNode (*list)[10] = Audio_Priority_Lists;
    for (int row = 0; row < rows; row++, list++) {
        for (int column = 0; column < 10; column++) {
            AudioListNode *node = Audio_List_First(&(*list)[column]);
            if (node != 0) {
                return (char *)node - 0xa4;
            }
        }
    }
    return 0;
}
