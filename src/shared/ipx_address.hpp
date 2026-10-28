#ifndef RA2_SHARED_IPX_ADDRESS_HPP
#define RA2_SHARED_IPX_ADDRESS_HPP
typedef unsigned char NetNumType[4];
typedef unsigned char NetNodeType[6];

// An IPX network and node address (constructor 0x00523410: all 0xFF).
// Under UDP (protocol 2, 0x007DDC70) the first word holds a port and the
// node an IP address.
// The network protocol (0x007DDC70: 1 IPX, 2 UDP). A global, not a static
// member: a static data member would renumber every including unit's _$E
// initializers.
extern int IPXProtocol;

class IPXAddressClass {
public:
    IPXAddressClass(NetNumType net, NetNodeType node, unsigned short socket); // 0x00523440
    void Get_Address(NetNumType net, NetNodeType node, unsigned short *socket); // 0x005234c0
    IPXAddressClass();                                              // 0x00523410
    void Get_Address(NetNumType net, NetNodeType node);             // 0x00523500
    void Set_Address(NetNumType net, NetNodeType node, unsigned short socket);   // 0x00523480
    int Is_Broadcast();                                             // 0x00523560
    bool operator==(IPXAddressClass &address);                      // 0x005235D0 (network and node; UDP: IP and port)
    bool unknown_523690(IPXAddressClass &address);                  // 0x00523690 (the node only: 4 bytes for UDP, else 6)
    void unknown_523960(unsigned short port);                       // 0x00523960 (UDP only: the port in the first word)
    char *As_String_00523840(IPXAddressClass const *address = 0); // optional address override, RET4
    void Get_Node(NetNodeType node);                                // 0x00523520
    void Set_Node(NetNodeType node);                                // 0x00523540
    bool operator!=(IPXAddressClass &address);                      // 0x005236C0
    bool operator>(IPXAddressClass &address);                       // 0x00523780 (the ten bytes as memcmp orders them)
    bool operator<(IPXAddressClass &address);                       // 0x005237B0
    bool operator>=(IPXAddressClass &address);                      // 0x005237E0
    bool operator<=(IPXAddressClass &address);                      // 0x00523810
    static void __fastcall Set_Protocol(int protocol);              // 0x00523950

    NetNumType NetworkNumber;           // +0x00
    NetNodeType NodeAddress;            // +0x04
    unsigned char unknown_0a[2];        // +0x0A (copied with the address: 12 bytes)
};

#endif
