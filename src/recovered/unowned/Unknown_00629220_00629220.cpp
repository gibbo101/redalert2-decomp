// void __fastcall Unknown_00629220(int start, int count, TargetClass whom, TargetClass const &target) (0x00629220)
// Retargets queued events: the first of the events start..start+count of the queue 0x00A35F30 whose target at
// +0x07 is whom gets target as its +0x13 target (name hypothesis; no callers found).
#include "shared/queue.hpp"
// @ref ?unknown_event_queue_a35f30@@3V?$QueueClass@VEventClass@@$0BAA@@@A=00a35f30

// Kind first, then ID (an inline helper: the original hoists the Kind byte load first).
inline bool Same_Target(TargetClass const &a, TargetClass const &b)
{
    return a.Kind == b.Kind && a.ID == b.ID;
}

void __fastcall Unknown_00629220(int start, int count, TargetClass whom, TargetClass const &target)
{
    for (int i = start; i <= start + count; i++) {
        if (Same_Target(whom, unknown_event_queue_a35f30[i].TargetAt(0x07))) {
            unknown_event_queue_a35f30[i].TargetAt(0x13) = target;
            return;
        }
    }
}
