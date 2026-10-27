// CommBufferClass: the send and receive packet queues of a connection
// (Combuf.cpp, 0x004800A0-0x00480AFB; vtable 0x0079DDB4, a virtual
// destructor only). Names follow Westwood's network queue (hypotheses; the
// layout comes from the constructor 0x004800C0, Init 0x00480280 and the
// queue functions).
//
// Layout (size 0x58):
//   +0x04  int MaxSend, +0x08 int MaxReceive, +0x0C int MaxPacketSize,
//   +0x10  int MaxExtraSize
//   +0x14  DelaySum, +0x18 NumDelay, +0x1C MeanDelay, +0x20 MaxDelay
//   +0x24  SendQueueType *SendQueue (0x24 each), +0x28 int SendCount,
//   +0x2C  unsigned SendTotal, +0x30 int *SendIndex
//   +0x34  ReceiveQueueType *ReceiveQueue (0x18 each), +0x38 int
//          ReceiveCount, +0x3C unsigned ReceiveTotal, +0x40 int *ReceiveIndex
//   +0x44..+0x54  debug configuration (Configure_Debug)
#ifndef RA2_SHARED_COMM_BUFFER_HPP
#define RA2_SHARED_COMM_BUFFER_HPP

#include "shared/system_timer.hpp"
#include "shared/crt_memory.hpp"

#include "shared/debug_printf.hpp"

// A count-up timer (hypothesis: Westwood's TTimerClass): the accumulated
// time plus the running time since Started (-1 while stopped).
template <class T>
class TTimerClass {
public:
    long Time() const
    {
        long value = Accumulated;
        if (Started != -1) {
            value += Timer - Started;
        }
        return value;
    }
    long Started;           // +0x00
    T Timer;                // +0x04
    long Accumulated;       // +0x08
};

// The network tick timer (0x00839980; hypothesis: TickCount).
extern TTimerClass<SystemTimerClass> TickCount;

// The header in front of every queued packet (14 bytes, packed).
#pragma pack(push, 1)
struct CommHeaderType {
    unsigned short MagicNumber;         // +0x00
    unsigned char Code;                 // +0x02 0 data with ACK, 1 data without, 2 ACK
    unsigned char unknown_03;           // +0x03 (Send_Packet's fourth argument)
    unsigned long PacketID;             // +0x04
    unsigned long unknown_08;           // +0x08
    unsigned short unknown_0c;          // +0x0C
};
#pragma pack(pop)

struct SendQueueType {
    unsigned int IsActive : 1;          // +0x00 bit 0
    unsigned int IsACK : 1;             //        bit 1
    unsigned int unknown_bit2 : 1;      //        bit 2 (retries or time exhausted)
    unsigned long FirstTime;            // +0x04
    unsigned long LastTime;             // +0x08
    unsigned long SendCount;            // +0x0C
    int BufLen;                         // +0x10
    char *Buffer;                       // +0x14
    int ExtraLen;                       // +0x18
    char *ExtraBuffer;                  // +0x1C
    unsigned short unknown_20;          // +0x20
};

struct ReceiveQueueType {
    unsigned int IsActive : 1;          // +0x00 bit 0
    unsigned int IsRead : 1;            //        bit 1
    unsigned int IsACK : 1;             //        bit 2
    unsigned long ReceiveTime;          // +0x04
    int BufLen;                         // +0x08
    char *Buffer;                       // +0x0C
    int ExtraLen;                       // +0x10
    char *ExtraBuffer;                  // +0x14
};

class CommBufferClass {
public:
    CommBufferClass(int numsend, int numreceive, int maxlen, int extralen);    // 0x004800C0
    virtual ~CommBufferClass();                                 // 0x004801D0

    void Init();                                                // 0x00480280
    void Init_Send_Queue();                                     // 0x00480370
    int Queue_Send(void *buf, int buflen, void *extrabuf, int extralen, unsigned short id);   // 0x004803F0
    int UnQueue_Send(void *buf, int *buflen, int index, void *extrabuf, int *extralen, unsigned short *id);   // 0x00480550
    SendQueueType *Get_Send(int index);                         // 0x00480700
    int Queue_Receive(void *buf, int buflen, void *extrabuf, int extralen);    // 0x00480730
    int UnQueue_Receive(void *buf, int *buflen, int index, void *extrabuf, int *extralen);   // 0x00480870
    ReceiveQueueType *Get_Receive(int index);                   // 0x004809C0
    void Add_Delay(unsigned long delay);                        // 0x004809F0
    unsigned long Avg_Delay();                                  // 0x00480A60
    unsigned long Max_Delay();                                  // 0x00480A70
    void Reset_Delay(bool clear);                               // 0x00480A80
    void Configure_Debug(int offset, int size, int names, int namestart, int namecount);   // 0x00480AB0

    int MaxSend;                        // +0x04
    int MaxReceive;                     // +0x08
    int MaxPacketSize;                  // +0x0C
    int MaxExtraSize;                   // +0x10
    unsigned long DelaySum;             // +0x14
    unsigned long NumDelay;             // +0x18
    unsigned long MeanDelay;            // +0x1C
    unsigned long MaxDelay;             // +0x20
    SendQueueType *SendQueue;           // +0x24
    int SendCount;                      // +0x28
    unsigned long SendTotal;            // +0x2C
    int *SendIndex;                     // +0x30
    ReceiveQueueType *ReceiveQueue;     // +0x34
    int ReceiveCount;                   // +0x38
    unsigned long ReceiveTotal;         // +0x3C
    int *ReceiveIndex;                  // +0x40
    int DebugOffset;                    // +0x44
    int DebugSize;                      // +0x48
    int DebugNames;                     // +0x4C
    int DebugNameStart;                 // +0x50
    int DebugNameCount;                 // +0x54
};

#endif
