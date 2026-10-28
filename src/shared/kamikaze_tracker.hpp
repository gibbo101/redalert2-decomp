// The tracker of spawned missiles flying at their targets (0x00A6E428; unit
// 0x00531360, whose dynamic initializer 0x00531550 builds a frame timer at +0
// and a vector at +0x0C). KamikazeTrackerClass is YRpp's name, a hypothesis;
// only the timer is declared.
#ifndef RA2_SHARED_KAMIKAZE_TRACKER_HPP
#define RA2_SHARED_KAMIKAZE_TRACKER_HPP

#include "shared/cd_timer.hpp"

class AbstractClass;
class AircraftClass;

class KamikazeTrackerClass {
public:
    void Add(AircraftClass *missile, AbstractClass *target);   // 0x005316A0
    void Detach(AircraftClass *missile);                       // 0x00531880

    CDTimerClass<FrameTimerClass> Timer;                        // +0x00
};

extern KamikazeTrackerClass KamikazeTracker;                   // 0x00A6E428

#endif
