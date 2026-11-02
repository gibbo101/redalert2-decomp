// Dynamic initializer of OutList (0x004D46D0, _$E; Tiberian Sun's globals.cpp): the
// queue's inline constructor builds its 128 empty events and then clears Count, Head
// and Tail (no destructor, so no atexit).
#include "shared/event.hpp"
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338

QueueClass<EventClass, 128> OutList;
