// The CRC of a wide name (0x005BBA50, ECX = the host name at 0x00A3F618): the packets carry it to
// identify the game (taunts, game options). Moved from shared/taunt_packet.hpp, whose partial
// HouseTypeClass cannot share a unit with shared/house.hpp.
#ifndef RA2_SHARED_NAME_CRC_HPP
#define RA2_SHARED_NAME_CRC_HPP

int __fastcall Unknown_005bba50(unsigned short *name);

#endif
