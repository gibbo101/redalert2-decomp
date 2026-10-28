// The tracker of spawned missiles flying at their targets (Kamikaze.cpp, unit
// 0x00531360: the global KamikazeTracker 0x00A6E428 built by the dynamic
// initializer 0x00531550, destroyed by 0x005315C0; members 0x00531650-0x00531B74).
// KamikazeTrackerClass and KamikazeControl are YRpp's names (the RTTI of
// DynamicVectorClass<KamikazeControl *> agrees on the second); member names
// are hypotheses.
#ifndef RA2_SHARED_KAMIKAZE_TRACKER_HPP
#define RA2_SHARED_KAMIKAZE_TRACKER_HPP

#include "shared/cd_timer.hpp"
#include "shared/com_persist.hpp"
#include "shared/vector_class_decl.hpp"

class AbstractClass;
class AircraftClass;
class CellClass;

// A missile and the cell it flies at (8 bytes).
class KamikazeControl {
public:
    AircraftClass *Unit;                                        // +0x00
    CellClass *Cell;                                            // +0x04
};

class KamikazeTrackerClass {
public:
    KamikazeTrackerClass();                                     // 0x00531650 (timer 100)
    ~KamikazeTrackerClass();                                    // 0x00531980
    void Add(AircraftClass *missile, AbstractClass *target);   // 0x005316A0
    void AI();                                                  // 0x005317C0
    void Detach(AbstractClass *target);                         // 0x00531880
    // Deletes every record and restarts the timer at 1.
    void Clear();                                               // 0x005319E0
    // The record count, then each record's eight bytes.
    HRESULT Save(IStream *stream);                              // 0x00531A40
    // Reads the records written by Save; their pointers are swizzled.
    HRESULT Load(IStream *stream);                              // 0x00531AA0

    CDTimerClass<FrameTimerClass> Timer;                        // +0x00
    DynamicVectorClass<KamikazeControl *> Nodes;                // +0x0C
};

extern KamikazeTrackerClass KamikazeTracker;                   // 0x00A6E428

#endif
