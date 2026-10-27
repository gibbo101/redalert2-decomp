#ifndef RA2_SHARED_IPX_ADDRESS_HPP
#define RA2_SHARED_IPX_ADDRESS_HPP
typedef unsigned char NetNumType[4];
typedef unsigned char NetNodeType[6];

// An IPX network and node address (constructor 0x00523410: all 0xFF).
// Under UDP (protocol 2, 0x007DDC70) the first word holds a port and the
// node an IP address.
class IPXAddressClass {
public:
    IPXAddressClass(NetNumType net, NetNodeType node, unsigned short socket); // 0x00523440
    void Get_Address(NetNumType net, NetNodeType node, unsigned short *socket); // 0x005234c0
    IPXAddressClass();                                              // 0x00523410
    void Get_Address(NetNumType net, NetNodeType node);             // 0x00523500
    void Set_Address(NetNumType net, NetNodeType node, int arg3);   // 0x00523480
    int Is_Broadcast();                                             // 0x00523560
    bool operator==(IPXAddressClass &address);                      // 0x005235D0 (network and node; UDP: IP and port)
    bool unknown_523690(IPXAddressClass &address);                  // 0x00523690 (the node only: 4 bytes for UDP, else 6)
    void unknown_523960(unsigned short port);                       // 0x00523960 (UDP only: the port in the first word)
    char *As_String_00523840(IPXAddressClass const *address = 0); // optional address override, RET4
    NetNumType NetworkNumber;           // +0x00
    NetNodeType NodeAddress;            // +0x04
    unsigned char unknown_0a[2];        // +0x0A (copied with the address: 12 bytes)
};

#endif
