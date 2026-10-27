// IPXGlobalConnClass: the broadcast/global IPX channel (ipxgconn.cpp,
// 0x00523FC0-0x00524E33; vtable 0x007A4684, 18 slots). Names follow
// Westwood's global IPX connection where the behaviour agrees (hypotheses).
//
// Layout (constructor 0x005241B0, destructor 0x00524290):
//   +0xB8  unsigned short ProductID
//   +0xC4  int (0), +0xC8 bool (true)
//   +0xCC  IPXAddressClass *unknown_cc   one per receive entry
//   +0xD0  int *unknown_d0               one per receive entry (-1)
//   +0xD4  int unknown_d4                the receive entry count
//   +0xD8  int unknown_d8
#ifndef RA2_SHARED_IPX_GLOBAL_CONN_HPP
#define RA2_SHARED_IPX_GLOBAL_CONN_HPP

#include "shared/ipx_conn.hpp"

// The header of a global packet: a CommHeaderType and the product ID.
#pragma pack(push, 1)
struct GlobalHeaderType : CommHeaderType {
    unsigned short ProductID;           // +0x0E
};
#pragma pack(pop)

// The empty wide string (0x00839D4C; shared/abstract_type.hpp declares it
// too): the global channel's connection name.
extern wchar_t const unknown_empty_wide_839d4c[];

class IPXGlobalConnClass : public IPXConnClass {
public:
    IPXGlobalConnClass(int numsend, int numreceive, int maxlen, unsigned short product_id, unsigned short magicnum);   // 0x005241B0
    virtual ~IPXGlobalConnClass();                                      // 0x00524290

    // The plain packet entry points stay ConnectionClass's (inline in the
    // header; emitted with the vtable).
    virtual int Send_Packet(void *buf, int buflen, int ack_req, unsigned char target)    // slot 2 0x00524D70
    {
        return ConnectionClass::Send_Packet(buf, buflen, ack_req, target);
    }
    virtual int Receive_Packet(void *buf, int buflen)                   // slot 3 0x00524D90
    {
        return ConnectionClass::Receive_Packet(buf, buflen);
    }
    virtual int Get_Packet(void *buf, int *buflen)                      // slot 4 0x00524DB0
    {
        return ConnectionClass::Get_Packet(buf, buflen);
    }
    virtual int unknown_slot6();                                        // slot 6 0x00524A30 (drops failed sends; their count)
    virtual int Service_Receive_Queue();                                // slot 8 0x00524830
    virtual int Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id);   // slot 9 0x005247B0
    virtual int Send_To(char *buf, int buflen, IPXAddressClass *address, unsigned char *immed, bool flagged, unsigned short id);   // slot 10 0x00524B50
    virtual int Send_Packet(void *buf, int buflen, IPXAddressClass *address, int ack_req, unsigned short id, unsigned long packet_id);   // slot 11 0x005242F0
    virtual int Receive_Packet(void *buf, int buflen, IPXAddressClass *address, unsigned short port);   // slot 12 0x005243D0
    virtual int Get_Packet(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id);   // slot 13 0x00524670
    virtual int unknown_slot14(int index, void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id, unsigned long *packet_id);   // slot 14 0x00524700 (reads a packet without marking it)
    virtual void unknown_slot15(int index);                             // slot 15 0x00524790 (marks a receive entry read)
    virtual int unknown_slot16(IPXAddressClass *address, unsigned short id);   // slot 16 0x00524AA0 (drops unacknowledged sends to an address)
    virtual int unknown_slot17(int arg1);                               // slot 17 0x00524870

    void unknown_524a10(int arg1);                                      // 0x00524A10

    unsigned short ProductID;           // +0xB8
    NetNumType BridgeNet;               // +0xBA
    NetNodeType BridgeNode;             // +0xBE
    int IsBridge;                       // +0xC4
    bool unknown_c8;                    // +0xC8
    IPXAddressClass *unknown_cc;        // +0xCC
    int *unknown_d0;                    // +0xD0
    int unknown_d4;                     // +0xD4
    int unknown_d8;                     // +0xD8
};

#endif
