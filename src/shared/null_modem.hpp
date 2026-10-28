// NullModemClass: the serial (null-modem and modem) connection manager
// (nullmgr.cpp; RTTI vtable 0x007A7414, base ConnManClass 0x007A474C) and
// its single connection, NullModemConnClass (vtable 0x007A73C8). Names follow
// Westwood's NULLMGR/NULLCONN (hypotheses where noted).
//
// Layout (constructor 0x005CFFC0):
//   +0x04 BuildBuf, +0x08 MaxLen, +0x0C ReceiveBuf, +0x10 ReceiveLen (500),
//   +0x14 ReceiveIndex, +0x18..+0x30 modem settings, +0x34 the modem
//   registry entry, +0x38 Connection, +0x3C NumConnections, +0x40 PortHandle,
//   +0x44 NumSend, +0x48 NumReceive, +0x4C MagicNum, +0x50 SendBuf,
//   +0x54 SendLen, +0x58 unknown, +0x5C..+0x64 timing, +0x68..+0x70 counters.
#ifndef RA2_SHARED_NULL_MODEM_HPP
#define RA2_SHARED_NULL_MODEM_HPP

#include "shared/connection.hpp"
#include "shared/conn_man.hpp"
#include "shared/win_modem.hpp"

// A modem found in the registry (0x1C bytes; constructor 0x0059CD00,
// destructor 0x0059D4F0; Westwood's ModemRegistryEntryClass).
class ModemRegistryEntryClass {
public:
    ModemRegistryEntryClass(int modem_number);                          // 0x0059CD00
    ~ModemRegistryEntryClass();                                         // 0x0059D4F0

    char *ModemName;                    // +0x00
    char *ModemDeviceName;              // +0x04 the port to open
    char unknown_08[0x1C - 0x08];
};

class NullModemConnClass : public ConnectionClass {
public:
    NullModemConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum);   // 0x005CDB40
    virtual ~NullModemConnClass() { delete SendBuf; }                   // scalar deleting 0x005CDCD0
    void Init(int port);                                                // 0x005CDBB0
    virtual void Init();                                                // slot 1 0x005CDCC0
    virtual int Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id);   // slot 9 0x005CDBD0

    int PortHandle;                     // +0x4C
    char *SendBuf;                      // +0x50
};

class NullModemClass : public ConnManClass {
public:
    NullModemClass(int numsend, int numreceive, int maxlen, unsigned short magicnum);   // 0x005CFFC0
    virtual ~NullModemClass();                                          // 0x005D0050 (deleting 0x005D2050)
    virtual int Service();                                              // 1 0x005D0660
    virtual int Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id);   // 2 0x005D1F60
    virtual int Get_Private_Message(void *buf, int *buflen, int *conn_id);   // 3 0x005D1FA0
    virtual int Num_Connections();                                      // 4 0x005D0350
    virtual int Connection_ID(int index);                               // 5 0x005D1F20
    virtual int Connection_Index(int id);                               // 6 0x005D1F30
    virtual int Global_Num_Send();                                      // 7 0x005D1FD0
    virtual int Global_Num_Receive();                                   // 8 0x005D1FF0
    virtual int Private_Num_Send(int id);                               // 9 0x005D2010
    virtual int Private_Num_Receive(int id);                            // 10 0x005D2030
    virtual void Reset_Response_Time(bool clear);                       // 11 0x005D0900
    virtual unsigned long Response_Time();                              // 12 0x005D08E0
    virtual void Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global);   // 13 0x005D05C0
    virtual void unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout);   // 14 0x005D1F40
    virtual void Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount);   // 15 0x005D0970

    int Delete_Connection();                                            // 0x005D0360
    int Init_Send_Queue();                                              // 0x005D03C0
    void Shutdown();                                                    // 0x005D0570
    int Send_Message(void *buf, int buflen, int ack_req);               // 0x005D05F0
    int Get_Message(void *buf, int *buflen);                            // 0x005D0630
    int Num_Send();                                                     // 0x005D08A0
    int Num_Receive();                                                  // 0x005D08C0
    void *Oldest_Send();                                                // 0x005D0920

    char *BuildBuf;                     // +0x04
    int MaxLen;                         // +0x08
    char *ReceiveBuf;                   // +0x0C
    int ReceiveLen;                     // +0x10 (500)
    int ReceiveIndex;                   // +0x14
    int unknown_18;                     // +0x18 (-1)
    int unknown_1c;                     // +0x1C
    int unknown_20;                     // +0x20
    int unknown_24;                     // +0x24 (3000)
    int unknown_28;                     // +0x28 (1200)
    int unknown_2c;                     // +0x2C (60)
    char unknown_30;                    // +0x30 ('+': the modem escape code)
    ModemRegistryEntryClass *ModemEntry;    // +0x34
    NullModemConnClass *Connection;     // +0x38
    int NumConnections;                 // +0x3C
    int PortHandle;                     // +0x40 (-1)
    int NumSend;                        // +0x44
    int NumReceive;                     // +0x48
    unsigned short MagicNum;            // +0x4C
    char *SendBuf;                      // +0x50
    int SendLen;                        // +0x54
    int unknown_58;                     // +0x58
    unsigned long RetryDelta;           // +0x5C (60)
    unsigned long MaxRetries;           // +0x60 (-1)
    unsigned long Timeout;              // +0x64 (1200)
    unsigned long SendOverflows;        // +0x68
    unsigned long ReceiveOverflows;     // +0x6C
    unsigned long CRCErrors;            // +0x70
};

#endif
