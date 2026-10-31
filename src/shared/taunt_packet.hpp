// The multiplayer taunt message sent by TauntCommandClass::Execute (0x0051B5F0; field names are
// hypotheses from that one writer) and the globals it reads.
#ifndef RA2_SHARED_TAUNT_PACKET_HPP
#define RA2_SHARED_TAUNT_PACKET_HPP

#include "shared/unknown_globals.hpp"
#include "shared/name_crc.hpp"

// A partial view of HouseTypeClass for this unit only (shared/house_type.hpp adds header statics
// that need their own accepted initializer sources; do not include both).
class HouseTypeClass {
public:
    char unknown_000[0x1A5];
    bool Multiplay;                 // +0x1A5
};

#pragma pack(push, 1)
struct UnknownTauntPacket {
    int Type;                       // +0x00 0x1D
    char Name[43];                  // +0x04 the sender's narrowed name
    unsigned char Muted;            // +0x2F set when the router reported a muted target
    union {
        unsigned char Packed;       // +0x30
        struct {
            unsigned char Taunt : 4;    // the taunt number
            unsigned char Country : 4;  // the sender's country
        };
    };
    int Session;                    // +0x31 session value 0x00A3D3B4
    int Checksum;                   // +0x35 0x005BBA50 of the host name
    char unknown_39[0x1C7 - 0x39];
};
#pragma pack(pop)

// When the last taunt was sent, in milliseconds (0x007DB560; -1 until the first).
extern unsigned long unknown_taunt_time_7db560;
// unknown_flag_a3f120, unknown_flag_a3f121: shared/unknown_globals.hpp.
// Unknown_005bba50: shared/name_crc.hpp.
// Unknown_Play_Taunt_00715fb0: shared/unknown_globals.hpp.

#endif
