// QueueClass<EventClass,128>::Add physical copy,004DE180.
// Instantiate the existing shared queue algorithm; native RA2 adds the
// timeGetTime stamp absent from the older Red Alert/TibSun Queue.H.
#include "shared/event.hpp"
template int QueueClass<EventClass, 128>::Add(EventClass const &event);
// @ref ?Add@?$QueueClass@VEventClass@@$0IA@@@QAEHABVEventClass@@@Z=004de180
