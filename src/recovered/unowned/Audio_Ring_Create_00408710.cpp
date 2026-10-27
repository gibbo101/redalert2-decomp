// AudioStream *Audio_Ring_Create() -- 0x00408710
// Purpose: makes an empty, zero-filled ring with its two queues (0 fills,
// 1 drains).
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);

AudioStream *Audio_Ring_Create()
{
    AudioStream *ring = (AudioStream *)operator new(sizeof(AudioStream));
    memset(ring, 0, sizeof(AudioStream));
    Audio_List_Init(&ring->Nodes);
    ring->Users = 0;
    for (int index = 0; index < 2; index++) {
        AudioQueue *queue = &ring->Queues[index];
        queue->Stream = ring;
        queue->Users = 0;
        queue->Error = 0;
        queue->Index = index;
        queue->unknown_18 = 0;
    }
    return ring;
}
