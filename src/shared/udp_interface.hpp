// UDPInterfaceClass: the Winsock UDP transport (_wsudp.cpp, 0x0076BE60-
// 0x0076D5A4; vtable 0x007AFB2C, 31 slots: the 23 WinsockInterfaceClass
// slots and 8 new). Names are hypotheses from the bodies and debug strings.
//
// Layout (constructor 0x0076C050):
//   +0x3F2FC  unsigned short (0; slot 24 reads it)
//   +0x3F300  SOCKET Sockets[8], +0x3F320 unsigned short SocketPorts[8],
//   +0x3F330  int NumSockets, +0x3F334 SOCKET (the socket for a port; -1)
//   +0x3F338  DynamicVectorClass<unsigned char *> BroadcastAddresses,
//   +0x3F350  unsigned short BroadcastPorts[256]
//   +0x3F550  DynamicVectorClass<unsigned char *> LocalAddresses
//   +0x3F568  int NumUnreachable, +0x3F56C unsigned long
//             UnreachableAddresses[16], +0x3F5AC unsigned short
//             UnreachablePorts[16]
#ifndef RA2_SHARED_UDP_INTERFACE_HPP
#define RA2_SHARED_UDP_INTERFACE_HPP

#include "shared/winsock_interface.hpp"
#include "shared/ipx_conn.hpp"

extern "C" int __cdecl sscanf(char const *string, char const *format, ...);         // 0x00783730

// The default game port (0x007F60D0).
extern int unknown_default_port_7f60d0;
// The alternate socket's port (0x007F60D8).
extern int unknown_alternate_port_7f60d8;
// The alternate socket's destination port on the loopback (0x007F60D4).
extern int unknown_port_7f60d4;
// Set once a malformed packet was seen (0x00B2AF1C).
extern bool unknown_b2af1c;

class UDPInterfaceClass : public WinsockInterfaceClass {
public:
    UDPInterfaceClass();                                                // 0x0076C050
    virtual ~UDPInterfaceClass();                                       // 0x0076C0F0
    virtual void unknown_slot3(void *buf, int buflen, void *address, int addresslen, bool alternate, unsigned char arg6, unsigned short arg7);   // slot 3 0x0076C960
    virtual void unknown_slot4(void *buf, int buflen, bool alternate);  // slot 4 0x0076C9C0
    virtual bool Start_Listening();                                     // slot 7 0x0076CB30
    virtual void Stop_Listening();                                      // slot 8 0x0076CBA0
    virtual void unknown_slot11(char *address, unsigned short port);    // slot 11 0x0076C290 (adds a broadcast address "a.b.c.d")
    virtual void unknown_slot12();                                      // slot 12 0x0076C230 (clears the broadcast addresses)
    virtual int unknown_slot13() { return 2; }                          // slot 13 0x0076D3E0 (inline)
    virtual unsigned int unknown_slot14(int socket);                    // slot 14 0x0076D3F0 (the notification message)
    virtual bool unknown_slot15(int socket);                            // slot 15 0x0076C6F0 (local addresses, then the alternate socket)
    virtual int unknown_slot16(int arg1, int arg2, int arg3, int arg4); // slot 16 0x0076CD40
    virtual int unknown_slot18() { return LocalAddresses.Count(); }     // slot 18 0x0076D430 (inline)
    virtual int unknown_slot19(int index) { return (int)LocalAddresses[index]; }   // slot 19 0x0076D440 (inline)
    virtual bool Open_Socket(unsigned short port);                      // slot 23 0x0076C350 (opens and binds the primary socket)
    virtual unsigned short unknown_slot24() { return unknown_3f2fc; }   // slot 24 0x0076D450 (inline)
    virtual bool unknown_slot25();                                      // slot 25 0x0076C6D0 (Init, then no sockets)
    virtual bool Open_Spare_Socket(unsigned short port);                // slot 26 0x0076C480
    virtual void Close_Spare_Socket(unsigned short port);               // slot 27 0x0076C5B0
    virtual void unknown_slot28();                                      // slot 28 0x0076CCC0
    virtual void unknown_slot29(unsigned short port);                   // slot 29 0x0076C670 (selects the socket for a port)
    virtual void unknown_slot30(unsigned long *address, unsigned short port);   // slot 30 0x0076CBC0 (marks an address unreachable)

    bool unknown_76cc70(unsigned long *address, unsigned short port);   // 0x0076CC70 (not marked unreachable)

    unsigned short unknown_3f2fc;                       // +0x3F2FC
    SOCKET Sockets[8];                                  // +0x3F300
    unsigned short SocketPorts[8];                      // +0x3F320
    int NumSockets;                                     // +0x3F330
    SOCKET unknown_3f334;                               // +0x3F334
    DynamicVectorClass<unsigned char *> BroadcastAddresses;     // +0x3F338
    unsigned short BroadcastPorts[256];                 // +0x3F350
    DynamicVectorClass<unsigned char *> LocalAddresses; // +0x3F550
    int NumUnreachable;                                 // +0x3F568
    unsigned long UnreachableAddresses[16];             // +0x3F56C
    unsigned short UnreachablePorts[16];                // +0x3F5AC
};

#endif
