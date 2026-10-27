// void __fastcall Audio_Ring_Add_Node(AudioStream *ring, AudioStreamNode *node) -- 0x00408A30
// Purpose: links node in at the head of the ring and counts its size.
#include "shared/audio.hpp"

void __fastcall Audio_Ring_Add_Node(AudioStream *ring, AudioStreamNode *node)
{
    Audio_List_Add_Head(&ring->Nodes, node);
    ring->NodeCount++;
    ring->Size += node->Size;
    node->Ring = ring;
    ring->Flags &= ~AUDIO_RING_FLAG_2;
}
