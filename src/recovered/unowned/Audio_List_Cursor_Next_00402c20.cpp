// AudioListNode *__fastcall Audio_List_Cursor_Next(AudioListCursor *cursor) -- 0x00402C20
// Purpose: the out-of-line copy of AudioListCursor::Next: advances the
// cursor when it has a node and returns its node.
// @ref ?Audio_List_Next@@YIPAUAudioListNode@@PAU1@@Z=00407310
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_List_Cursor_Next(AudioListCursor *cursor)
{
    return cursor->Next();
}
