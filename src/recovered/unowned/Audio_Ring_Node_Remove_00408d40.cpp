// void __fastcall Audio_Ring_Node_Remove(AudioStreamNode *node) -- 0x00408D40
// Purpose: unlinks the node from its ring and uncounts its size.
#include "shared/audio.hpp"

void __fastcall Audio_Ring_Node_Remove(AudioStreamNode *node)
{
    Audio_List_Remove(node);
    AudioStream *ring = node->Ring;
    node->Ring = 0;
    ring->NodeCount--;
    ring->Size -= node->Size;
    ring->Flags &= ~AUDIO_RING_FLAG_2;
}
