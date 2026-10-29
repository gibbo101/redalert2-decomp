// bool __stdcall Unknown_0062E670(EventClass event) (0x0062E670): stamps the frame and adds the event to OutList.
#include "shared/queue.hpp"
// @ref ?Frame@@3HA=00a40d2c

bool __stdcall Unknown_0062E670(EventClass event)
{
    event.Frame = ::Frame;
    return OutList.Add(event);
}
