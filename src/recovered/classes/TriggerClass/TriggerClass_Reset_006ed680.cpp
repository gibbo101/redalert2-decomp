// void TriggerClass::Reset() (0x006ED680)
// Restarts the timed events: elapsed time (13) waits Data seconds, random
// delay (51) Data / 2 plus a Random_Pick in [0, Data]; their fired bits
// clear (TibSun Reset_All_Timed_Events shape).
#include "shared/object.hpp"
#include "shared/random.hpp"

void TriggerClass::Reset()
{
    int index = 0;
    TEventClass *event = Class->Events;
    while (event != 0) {
        if (event->Type == 0x0D) {
            Timer = event->Data * 15;
            Events &= ~(1 << index);
        }
        if (event->Type == 0x33) {
            Timer = (event->Data / 2 + Random_Pick(0, event->Data)) * 15;
            Events &= ~(1 << index);
        }
        index++;
        event = event->Next;
    }
}
