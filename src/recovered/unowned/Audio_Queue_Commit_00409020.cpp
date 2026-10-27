// int __fastcall Audio_Queue_Commit(AudioQueue *queue) -- 0x00409020
// Purpose: commits the queue's pending bytes: counts them consumed here
// and queued on the other queue, releases them from the node windows
// starting at the commit node (a fully used window is reset to its node's
// whole buffer), makes the reached node the new commit and current node,
// clears the at-head flag and refreshes the queue (0x004090E0). Returns
// the bytes committed.
// @ref ?Audio_Queue_Update@@YIHPAUAudioQueue@@H@Z=004090e0
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Commit(AudioQueue *queue)
{
    int pending = queue->Pending;
    if (pending == 0) {
        return 0;
    }
    AudioQueue *partner = Audio_Queue_Partner(queue);
    queue->Consumed += pending;
    partner->Queued += pending;
    int committed = pending;
    AudioStreamNode *node = queue->CommitNode;
    while (pending != 0) {
        AudioStreamWindow *window = &node->Windows[queue->Index];
        if (window->Length <= pending) {
            pending -= window->Length;
            window->Pointer = node->Base;
            window->Length = node->Size;
            node = node->Ring_Next();
        } else {
            window->Pointer += pending;
            window->Length -= pending;
            pending = 0;
        }
    }
    queue->CommitNode = node;
    Audio_Queue_Rewind(queue);
    return committed;
}
