// AudioStreamNode *__fastcall Audio_Ring_Node_Create(int size, int shift) -- 0x00408CA0
// Purpose: makes an unlinked node with a buffer of size bytes aligned to
// 1 << shift. Returns 0 when the buffer cannot be allocated.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

AudioStreamNode *__fastcall Audio_Ring_Node_Create(int size, int shift)
{
    AudioStreamNode *node = (AudioStreamNode *)operator new(sizeof(AudioStreamNode));
    memset(node, 0, sizeof(AudioStreamNode));
    Audio_List_Init_Node(node);
    node->Data = operator new((1 << shift) + size);
    if (node->Data == 0) {
        if (node != 0) {
            operator delete(node);
        }
        return 0;
    }
    node->Shift = shift;
    node->Base = (char *)(((1 << shift) + (int)node->Data - 1) & (-1 << shift));
    node->Size = size;
    return node;
}
