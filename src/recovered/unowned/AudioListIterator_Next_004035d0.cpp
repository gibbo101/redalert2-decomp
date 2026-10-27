// AudioListNode *AudioListIterator::Next() -- 0x004035D0
// Purpose: advances the iterator to the next node of its list (a null
// iterator stays null) and returns it.
// @ref ?Audio_List_Next@@YIPAUAudioListNode@@PAU1@@Z=00407310
#include "shared/audio.hpp"

AudioListNode *AudioListIterator::Next()
{
    if (Node != 0) {
        Node = Audio_List_Next(Node);
    }
    return Node;
}
