// One placed beacon of the multiplayer game (hypothesis; the object at 0x0084E8D0,
// shared/unknown_globals.hpp, keeps three per house). 0x0042DA20 draws the marker and its text.
#ifndef RA2_SHARED_BEACON_HPP
#define RA2_SHARED_BEACON_HPP

#include "shared/unknown_globals.hpp"
#include "shared/coord.hpp"
#include "shared/rect.hpp"

// The text of a beacon: a fixed wide-character buffer copied by value.
struct UnknownBeaconText {
    unsigned short chars[128];
};

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

class UnknownBeacon {
public:
    UnknownBeacon();                                        // reads the default position of unknown_object_84e8d0
    void Unknown_0042DA20(Surface *surface, Rect rect);
    void Unknown_0042DE20(Surface *surface, Rect rect, int arg3);   // 0x0042DE20     // 0x0042DA20 (draws the marker and its text)

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

inline UnknownBeacon::UnknownBeacon()
{
    unknown_coord = unknown_object_84e8d0.unknown_80;
    unknown_flags &= 0xfc;
    for (int index = 0; index < 128; index++) {
        unknown_text.chars[index] = 0;
    }
}

// The beacon manager's constructor and destructor (inline in the original; the
// definition of unknown_object_84e8d0 expands them into its initializer and exit thunk).
inline Unknown84E8D0::Unknown84E8D0()
{
    for (int house = 0; house < 8; house++) {
        for (int slot = 0; slot < 3; slot++) {
            unknown_00[house][slot] = 0;
        }
    }
    unknown_60 = 0;
    unknown_7c = 0;
}

inline Unknown84E8D0::~Unknown84E8D0()
{
    if (unknown_60) {
        for (int house = 0; house < 8; house++) {
            for (int slot = 0; slot < 3; slot++) {
                if (unknown_00[house][slot]) {
                    delete unknown_00[house][slot];
                    unknown_00[house][slot] = 0;
                }
            }
        }
        unknown_60 = 0;
    }
}

#endif
