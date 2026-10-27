// void __fastcall Audio_Ring_Node_Destroy(AudioStreamNode *node) -- 0x00408D20
// Purpose: frees the node's buffer and the node.
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Ring_Node_Destroy(AudioStreamNode *node)
{
    if (node->Data != 0) {
        operator delete(node->Data);
    }
    operator delete(node);
}
