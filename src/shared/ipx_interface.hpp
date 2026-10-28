// IPXInterfaceClass: the Winsock IPX transport (_wsipx.cpp, 0x00769EA0-
// 0x0076AA8B; vtable 0x007AFA0C, 23 slots). Names are hypotheses from the
// debug strings.
//
// Layout (constructor 0x0076A070; size 0x3F310):
//   +0x3F2FC  NetNumType Network (all 0xFF), +0x3F300 NetNodeType Node,
//   +0x3F306  NetNodeType unknown_3f306 (all 0xFF)
#ifndef RA2_SHARED_IPX_INTERFACE_HPP
#define RA2_SHARED_IPX_INTERFACE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_string.hpp"
extern "C" unsigned int __cdecl strlen(char const *string);
#pragma intrinsic(strlen)

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);              // 0x007820F4

// Windows version facts (0x00839C4C: a Windows 9x flag; 0x00839BC0 and
// 0x00839BC4: hypothesis, the major and minor version).
extern int unknown_839bc0;
extern int unknown_839bc4;

// An IPX socket address (SOCKADDR_IPX, 14 bytes).
#pragma pack(push, 1)
struct UnknownIPXSocketAddress {
    short sa_family;                    // +0x00
    unsigned char sa_netnum[4];         // +0x02
    unsigned char sa_nodenum[6];        // +0x06
    unsigned short sa_socket;           // +0x0C
};
#pragma pack(pop)

// IPX_ADDRESS_DATA (24 bytes).
struct UnknownIPXAddressData {
    int adapternum;                     // +0x00
    unsigned char netnum[4];            // +0x04
    unsigned char nodenum[6];           // +0x08
    unsigned char wan;
    unsigned char status;
    int maxpkt;                         // +0x10
    unsigned long linkspeed;            // +0x14
};

// A malformed IPX packet was seen (0x00B2AE24).
extern bool unknown_malformed_seen_b2ae24;

class IPXInterfaceClass : public WinsockInterfaceClass {
public:
    IPXInterfaceClass();                                                // 0x0076A070
    virtual int unknown_slot13() { return 1; }                          // slot 13 0x0076AA50 (inline)
    virtual unsigned int unknown_slot14(int socket) { return 0x473; }   // slot 14 0x0076AA60 (inline; the notification message)
    virtual bool unknown_slot15(int socket_number);                     // slot 15 0x0076A3A0 (opens the socket)
    virtual int unknown_slot16(int window, int message, int wparam, int lparam);   // slot 16 0x0076A6B0 (the notification handler)

    int Get_Network_Card_Address(int card_number, UnknownIPXSocketAddress *address);   // 0x0076A0B0
    int unknown_76a230(int card_number, char *buffer, int length);      // 0x0076A230 (the card address as text)

    unsigned char Network[4];           // +0x3F2FC
    unsigned char Node[6];              // +0x3F300
    unsigned char unknown_3f306[6];     // +0x3F306
    int SocketNumber;                   // +0x3F30C the IPX socket number (size 0x3F310)
};

#endif
