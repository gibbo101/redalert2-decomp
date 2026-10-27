// AudioListNode *__fastcall Audio_Cursor_Advance(AudioListCursor *cursor) -- 0x004031F0
// Purpose: moves a list cursor to the next node (it stays at the end) and
// returns it. The same walk as 0x00402C20, for another user of the cursor.
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_Cursor_Advance(AudioListCursor *cursor)
{
    if (cursor->Node != 0) {
        cursor->Node = Audio_List_Next(cursor->Node);
    }
    return cursor->Node;
}
