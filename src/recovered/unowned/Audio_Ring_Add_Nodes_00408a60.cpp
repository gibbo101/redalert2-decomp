// int __fastcall Audio_Ring_Add_Nodes(AudioStream *ring, int count, int size, int shift) -- 0x00408A60
// Purpose: adds count nodes of size bytes aligned to 1 << shift
// (Audio_Ring_Node_Create and Audio_Ring_Add_Node expanded inline).
// Returns how many were added.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Add_Nodes(AudioStream *ring, int count, int size, int shift)
{
    int added = 0;
    while (count-- != 0) {
        AudioStreamNode *node = Audio_Ring_Node_Create(size, shift);
        if (node == 0) {
            break;
        }
        Audio_Ring_Add_Node(ring, node);
        added++;
    }
    return added;
}
