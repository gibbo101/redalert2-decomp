// RadarEventClass (RadarEvent.cpp; field and member names from the TS reconstruction's revent.h/revent.cpp,
// offsets from the constructor 0x0063B6C0 and Process 0x0063B940): a radar ping in the list at 0x00AB67E8
// (RadarEventClass::RadarEvents in TS). Older RadarEventClass sources declare their own one-member
// stand-ins; units that include this header use this layout. RA2 keeps the per-type values in a static
// table (0x007A8D58) where TS read the rules lists, and replaces TS's LastRadarEventCell with an
// eight-cell ring (0x00AB6788).
#ifndef RA2_SHARED_RADAR_EVENT_CLASS_HPP
#define RA2_SHARED_RADAR_EVENT_CLASS_HPP

#include "shared/vector_class.hpp"
#include "shared/cd_timer.hpp"
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/rgb_class.hpp"

// The event kind (index into the table at 0x007A8D58; RA2 has 13; names hypotheses after TS).
enum RadarEventType {
    RADAREVENT_NONE = -1,
    RADAREVENT_COMBAT = 0
};

// One row of the per-type table at 0x007A8D58 (16 bytes; row 0 is {8, 200, 400, 1}).
struct UnknownRadarEventType_7a8d58 {
    int SuppressionDistance;    // +0x00 (0x0063C630)
    int VisibilityDuration;     // +0x04 (0x0063C610)
    int Duration;               // +0x08 (0x0063C620)
    bool CanSuppress;           // +0x0C (0x0063B6B0)
};
extern UnknownRadarEventType_7a8d58 unknown_radar_event_types_7a8d58[];

class RadarEventClass;
// Every radar event (0x00AB67E8).
extern DynamicVectorClass<RadarEventClass *> unknown_radar_events_ab67e8;

// The ring of the last eight event cells (0x00AB6788), its newest entry (0x00AB67C8, -1 when empty), the
// entry the "go to event" key last showed (0x00AB6818) and the empty cell (0x00AB67A8).
extern Cell unknown_event_cells_ab6788[8];
extern Cell unknown_event_empty_cell_ab67a8;
extern int unknown_event_last_ab67c8;
extern int unknown_event_current_ab6818;
// Saved after the events (0x00AB67B8).
extern int unknown_radar_event_word_ab67b8;

void __fastcall RadarEventClass_unknown_remember_cell(Cell const &cell);    // 0x0063C6C0
Cell __fastcall RadarEventClass_unknown_newest_cell();                      // 0x0063C6F0
Cell __fastcall RadarEventClass_unknown_previous_cell();                    // 0x0063C720

class RadarEventClass {
public:
    RadarEventClass(RadarEventType type, Cell cell);    // 0x0063B6C0
    // Takes the event out of the list (0x0063B840; TS ~RadarEventClass; inlined after it in its unit).
    ~RadarEventClass();
    // Per-frame update (0x0063B940; TS RadarEventClass::Process).
    void Unknown_0063B940();
    // Draws the event on the radar (0x0063BB90; TS RadarEventClass::Draw).
    void Draw();
    void Plot();                                        // 0x0063C080
    void Get_Event_Rect(Point2D (&event_rect)[4]) const;  // 0x0063C270
    RGBClass Get_Max_Color() const;                     // 0x0063C490
    RGBClass Get_Min_Color() const;                     // 0x0063C550
    // TS Get_Visibility_Duration, Get_Duration and Get_Suppression_Distance (0x0063C610, 0x0063C620, 0x0063C630).
    int Unknown_0063C610() const;
    int Unknown_0063C620() const;
    int Unknown_0063C630() const;
    // Draws every event still visible or rotating (0x0063BB40).
    static void Draw_Events();
    // Deletes every event whose duration has run out and that is not rotating (0x0063BEF0).
    static void Remove_Finished();

    RadarEventType Type;                            // +0x00
    Point2D Offset;                                 // +0x04 from the radar rectangle's corner
    float Radius;                                   // +0x0C
    float RotationAngle;                            // +0x10
    float RotationSpeed;                            // +0x14
    float ColorFactor;                              // +0x18
    float ColorSpeed;                               // +0x1C
    Cell Location;                                  // +0x20
    CDTimerClass<FrameTimerClass> DurationTimer;    // +0x24
    CDTimerClass<FrameTimerClass> VisibilityTimer;  // +0x30
    bool IsRotating;                                // +0x3C
    bool IsVisible;                                 // +0x3D
};

// Whether events of this type are dropped near an existing one (0x0063B6B0; TS Can_Suppress_Radar_Event).
bool __fastcall Can_Suppress_Radar_Event(RadarEventType event);
// Marks one radar pixel (0x0063B6A0; the plotter of RadarEventClass::Plot).
void __fastcall Plot_Radar_Event_Point(Point2D const &point);
bool __fastcall Submit_Radar_Event(RadarEventType event, Cell cell);           // 0x0063B5B0
bool __fastcall Try_Suppress_Radar_Event(RadarEventType event, Cell cell);     // 0x0063BFA0

#endif
