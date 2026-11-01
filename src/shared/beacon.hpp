// One placed beacon of the multiplayer game (hypothesis; the object at 0x0084E8D0,
// shared/unknown_globals.hpp, keeps three per house). 0x0042DA20 draws the marker and its text.
#ifndef RA2_SHARED_BEACON_HPP
#define RA2_SHARED_BEACON_HPP

// The Beacon unit's own Unknown84E8D0 members (shared/unknown_globals.hpp guards them: new declarations
// there renumber Refresh_Wonline_Players 0x0073FEE0); the unit defines both guards in its first draft.

#include "shared/unknown_globals.hpp"
#include "shared/coord.hpp"
#include "shared/rect.hpp"

// The text of a beacon: a fixed wide-character buffer copied by value.
struct UnknownBeaconText {
    unsigned short chars[128];
};

// The packets copy the sender's narrowed name with the intrinsic strcpy.
extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)

// The beacon placement (type 0x20) and removal (0x21) message of 0x0042E370 and 0x0042E990 (the first 61 bytes are
// sent; the buffer has the size of the taunt message, 0x1C7; names are hypotheses).
#pragma pack(push, 1)
struct UnknownBeaconPacket {
    int Type;                       // +0x00 0x20 placed, 0x21 removed
    char Name[43];                  // +0x04 the sender's narrowed name
    int X;                          // +0x2F
    int Y;                          // +0x33
    int Z;                          // +0x37
    unsigned char Slot;             // +0x3B
    unsigned char House;            // +0x3C
    char unknown_3d[0x1C7 - 0x3D];
};
#pragma pack(pop)

// The beacon text message (type 0x22) of 0x0042EC20 (the whole 0x1C7-byte buffer is sent; names are
// hypotheses): the slot is -1 until the sender finds its beacon.
#pragma pack(push, 1)
struct UnknownBeaconTextPacket {
    int Type;                       // +0x00 0x22
    char Name[43];                  // +0x04 the sender's narrowed name
    char Slot;                      // +0x2F
    char House;                     // +0x30
    unsigned short Text[0x80];      // +0x31
    char unknown_131[0x1C7 - 0x131];
};
#pragma pack(pop)

class UnknownBeacon {
public:
    UnknownBeacon();                                        // 0x0042D9E0 (the default position, cleared flags and text)
    void Unknown_0042DD60(CoordStruct coord, int house);    // 0x0042DD60 (places it: a non-default position, a house < 8)
    void Unknown_0042DDF0(unsigned short const *text);       // 0x0042DDF0 (sets the text, at most 127 characters; none: empty)
    bool Unknown_0042E080();                                // 0x0042E080 (placed by a mutual ally that is not defeated)
    void Unknown_0042DA20(Surface *surface, Rect rect);
    void Unknown_0042DE20(Surface *surface, Rect rect, bool forced);   // 0x0042DE20 (the radar marker; forced: drawn off the blink phase too)

    CoordStruct unknown_coord;      // +0x00
    unsigned char unknown_flags;    // +0x0C bit 0 placed, bit 1 blinking
    unsigned char unknown_0d;
    UnknownBeaconText unknown_text; // +0x0E
    int unknown_house;              // +0x110 the owner's index in Houses
};

struct ShapeFileStruct;
extern ShapeFileStruct const *unknown_beacon_shape_84e98c;          // 0x0084E98C PBEACON.SHP (Unknown84E8D0 0x0042E1A0)
extern ShapeFileStruct const *unknown_radar_beacon_shape_84e990;    // 0x0084E990 RDRBEACN.SHP
extern int unknown_beacon_phase_84e948;                             // 0x0084E948 (the blink phase length; hypothesis)
extern int unknown_beacon_cycle_84e93c;                             // 0x0084E93C (twice the beacon's animation frame count; hypothesis)

// The distance between two coordinates, both taken by value (0x0042E860 and the 0x0042E740 that
// expands it load the beacon's coordinate before the point's; a reference argument does not).
double __cdecl unknown_sqrt_4ba410(double value);     // 0x004BA410
inline int Beacon_Distance(CoordStruct a, CoordStruct b)
{
    CoordStruct d(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    return (int)unknown_sqrt_4ba410((double)d.X * d.X + (double)d.Z * d.Z + (double)d.Y * d.Y);
}

#endif
