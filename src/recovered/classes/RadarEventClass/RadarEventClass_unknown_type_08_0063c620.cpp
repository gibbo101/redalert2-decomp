// int RadarEventClass::Unknown_0063C620() const -- 0x0063C620
// Purpose: field +0x08 of the event type entry selected by the event's
// type (+0x00), from the 16-byte table at 0x007A8D58 (entry 0 is
// {8, 200, 400, 1}).
// Assumptions: the table's meaning and the field names are not identified;
// the event's type is its first member.

struct UnknownRadarEventType_7a8d58 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
};
extern UnknownRadarEventType_7a8d58 unknown_radar_event_types_7a8d58[];
// @ref ?unknown_radar_event_types_7a8d58@@3PAUUnknownRadarEventType_7a8d58@@A=007a8d58

class RadarEventClass {
public:
    int Unknown_0063C620() const;

    int Type;
};

int RadarEventClass::Unknown_0063C620() const
{
    return unknown_radar_event_types_7a8d58[Type].unknown_08;
}
