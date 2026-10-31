// The game options packet of netshare.cpp (global commands 0x17 public and 0x18 private, 0x1C7
// bytes like every global packet; Send_Game_Options_005c3c60 0x005C3C60 and 0x005C3D90 fill it).
// A view of the global packet (shared/unknown_globals.hpp UnknownGlobalPacket) kept in its own
// header, as UnknownTauntPacket is: a new member type in UnknownGlobalPacket shifts code in
// units that never send this packet (wonline.cpp 0x0073FEE0).
#ifndef RA2_SHARED_GAME_OPTIONS_PACKET_HPP
#define RA2_SHARED_GAME_OPTIONS_PACKET_HPP

#include "shared/unknown_globals.hpp"
#include "shared/name_crc.hpp"

#pragma pack(push, 1)
struct UnknownOptionsPacket {
    int Command;                        // +0x00 0x17 or 0x18
    char Name[0x2F - 0x04];             // +0x04 the sender's nick name (unknown_name_a3d3a0)
    char Text[0x1BF - 0x2F];            // +0x2F the options text (narrow)
    int Color;                          // +0x1BF the sender's colour (session +0x11C)
    int NameCRC;                        // +0x1C3 Unknown_005bba50 of the host's name
};
#pragma pack(pop)

#endif
