// RadarEventClass (RadarEvent.cpp; field names from the TS reconstruction's revent.h, offsets from
// 0x0063BB40 and 0x0063BEF0): a radar ping in the list at 0x00AB67E8 (RadarEventClass::RadarEvents in TS). Older
// RadarEventClass sources declare their own one-member stand-ins; units that include this header
// use this layout.
#ifndef RA2_SHARED_RADAR_EVENT_CLASS_HPP
#define RA2_SHARED_RADAR_EVENT_CLASS_HPP

#include "shared/vector_class.hpp"
#include "shared/cd_timer.hpp"

class RadarEventClass;
// Every radar event (0x00AB67E8).
extern DynamicVectorClass<RadarEventClass *> unknown_radar_events_ab67e8;

class RadarEventClass {
public:
    // Takes the event out of the list (0x0063B840; TS ~RadarEventClass; inlined after it in its unit).
    ~RadarEventClass();
    // Per-frame update (0x0063B940, not yet recovered; TS RadarEventClass::Process).
    void Unknown_0063B940();
    // Draws the event on the radar (0x0063BB90, not yet recovered; TS RadarEventClass::Draw).
    void Draw();
    // Draws every event still visible or rotating (0x0063BB40).
    static void Draw_Events();
    // Deletes every event whose duration has run out and that is not rotating (0x0063BEF0).
    static void Remove_Finished();

    char unknown_00[0x24];
    CDTimerClass<FrameTimerClass> DurationTimer;    // +0x24
    CDTimerClass<FrameTimerClass> VisibilityTimer;  // +0x30
    bool IsRotating;                                // +0x3C
};

#endif
