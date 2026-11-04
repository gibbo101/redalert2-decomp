// Initializes a radar ping, its cell history and its active-list entry.
#include "shared/radar_event_class.hpp"
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

RadarEventClass::RadarEventClass(RadarEventType type, Cell cell)
    : Type(type), RotationAngle(0.7853981633974483f),
      RotationSpeed(Rules->RadarEventRotationSpeed), ColorFactor(0),
      ColorSpeed(Rules->RadarEventColorSpeed), Location(cell),
      DurationTimer(0), VisibilityTimer(0), IsRotating(true), IsVisible(true)
{
    Offset = Map.Unknown_00631470(cell).Top_Left() - Map.unknown_1498.Top_Left();
    Radius = MAX(Offset.X, MAX(Offset.Y, MAX(Map.unknown_1498.Width - Offset.X, Map.unknown_1498.Height - Offset.Y)));
    RadarEventClass_unknown_remember_cell(cell);
    unknown_radar_events_ab67e8.Add(this);
}
