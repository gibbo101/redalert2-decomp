// void __fastcall Audio_Ring_Clear(AudioStream *ring) -- 0x00408890
// Purpose: removes and frees every node of the ring, then resets it
// (Audio_Ring_Node_Remove, Audio_Ring_Node_Destroy and Audio_Ring_Reset
// expanded inline).
#include "shared/audio.hpp"

void __fastcall Audio_Ring_Clear(AudioStream *ring)
{
    AudioStreamNode *node;
    while ((node = (AudioStreamNode *)ring->Nodes.Next) != (AudioStreamNode *)&ring->Nodes) {
        Audio_Ring_Node_Remove(node);
        Audio_Ring_Node_Destroy(node);
    }
    Audio_Ring_Reset(ring);
}
