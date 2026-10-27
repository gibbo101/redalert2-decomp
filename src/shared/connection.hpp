// ConnectionClass: a reliable packet connection over a CommBufferClass
// queue (Connect.cpp, 0x00480C30-0x0048164F; vtable 0x0079DDCC, 10 slots,
// slot 9 Send pure). Names follow Westwood's connection class (hypotheses;
// the layout comes from the constructor 0x00480E20 and Init 0x00480ED0).
//
// Layout (size 0x4C):
//   +0x04  CommBufferClass *Queue
//   +0x08..+0x18  statistics (resends, receive loss, failures, bad magic)
//   +0x1C  int MaxPacketLen (maxlen + header), +0x20 char *PacketBuf
//   +0x24  unsigned short MagicNum, +0x28 RetryDelta, +0x2C MaxRetries,
//   +0x30  Timeout (-1: none)
//   +0x34  NumRecNoAck, +0x38 NumRecAck, +0x3C NumSendNoAck,
//   +0x40  NumSendAck, +0x44 LastSeqID, +0x48 LastReadID (-1 after Init)
#ifndef RA2_SHARED_CONNECTION_HPP
#define RA2_SHARED_CONNECTION_HPP

#include "shared/unknown_globals.hpp"
#include "shared/comm_buffer.hpp"

// Packet codes (CommHeaderType::Code).
enum {
    PACKET_DATA_ACK = 0,
    PACKET_DATA_NOACK = 1,
    PACKET_ACK = 2,
    PACKET_COUNT = 3
};

// A game-mode value (0x00A3D298; shared/object.hpp names it too).
// Forwarding flag (0x00A3FBA8): the header's fourth byte carries a target.
extern bool unknown_flag_a3fba8;

class ConnectionClass;
// The connection whose sends are flagged (0x00A409C4).
extern ConnectionClass *unknown_connection_a409c4;

class ConnectionClass {
public:
    ConnectionClass(int numsend, int numreceive, int maxlen, unsigned short magicnum,
        unsigned long retry_delta, unsigned long max_retries, unsigned long timeout, int extralen = 0);   // 0x00480E20
    virtual ~ConnectionClass();                                         // 0x00480EA0 (slot 0)
    virtual void Init();                                                // slot 1 0x00480ED0
    virtual int Send_Packet(void *buf, int buflen, int ack_req, unsigned char target);   // slot 2 0x00480F00
    virtual int Receive_Packet(void *buf, int buflen);                  // slot 3 0x00481000
    virtual int Get_Packet(void *buf, int *buflen);                     // slot 4 0x004812E0
    virtual int Service();                                              // slot 5 0x00481370
    virtual int unknown_slot6();                                        // slot 6 0x00481550
    virtual int Service_Send_Queue();                                   // slot 7 0x004813A0
    virtual int Service_Receive_Queue();                                // slot 8 0x00481560
    virtual int Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id) = 0;   // slot 9

    static unsigned long Time();                                        // 0x004815C0
    static char *__fastcall Command_Name(int command);                  // 0x004815F0
    static char *Commands[PACKET_COUNT];                                // 0x007D30DC

    CommBufferClass *Queue;             // +0x04
    unsigned long unknown_08;           // +0x08 resends
    unsigned long unknown_0c;           // +0x0C packets lost (no-ACK stream)
    unsigned long unknown_10;           // +0x10 percent received (no-ACK stream)
    unsigned long unknown_14;           // +0x14 receive failures
    unsigned long unknown_18;           // +0x18 bad magic numbers
    int MaxPacketLen;                   // +0x1C
    char *PacketBuf;                    // +0x20
    unsigned short MagicNum;            // +0x24
    unsigned long RetryDelta;           // +0x28
    unsigned long MaxRetries;           // +0x2C
    unsigned long Timeout;              // +0x30
    unsigned long NumRecNoAck;          // +0x34
    unsigned long NumRecAck;            // +0x38
    unsigned long NumSendNoAck;         // +0x3C
    unsigned long NumSendAck;           // +0x40
    unsigned long LastSeqID;            // +0x44
    unsigned long LastReadID;           // +0x48
};

#endif
