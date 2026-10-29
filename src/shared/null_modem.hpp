// NullModemClass: the serial (null-modem and modem) connection manager
// (nullmgr.cpp; RTTI vtable 0x007A7414, base ConnManClass 0x007A474C) and
// its single connection, NullModemConnClass (vtable 0x007A73C8). Names follow
// Westwood's NULLMGR/NULLCONN (hypotheses where noted).
//
// Layout (constructor 0x005CFFC0):
//   +0x04 BuildBuf, +0x08 MaxLen, +0x0C ReceiveBuf, +0x10 ReceiveLen (500),
//   +0x14 ReceiveIndex, +0x18..+0x30 modem settings, +0x34 the modem
//   registry entry, +0x38 Connection, +0x3C NumConnections, +0x40 PortHandle,
//   +0x44 NumSend, +0x48 NumReceive, +0x4C MagicNum, +0x50 RXBuf,
//   +0x54 RXSize, +0x58 RXCount, +0x5C..+0x64 timing, +0x68..+0x70 counters.
#ifndef RA2_SHARED_NULL_MODEM_HPP
#define RA2_SHARED_NULL_MODEM_HPP

#include "shared/connection.hpp"
#include "shared/conn_man.hpp"
#include "shared/win_modem.hpp"
#include "shared/keyboard.hpp"

// A modem found in the registry (0x1C bytes; constructor 0x0059CD00,
// destructor 0x0059D4F0; Westwood's ModemRegistryEntryClass).
class ModemRegistryEntryClass {
public:
    ModemRegistryEntryClass(int modem_number);                          // 0x0059CD00
    ~ModemRegistryEntryClass();                                         // 0x0059D4F0
    // Frees the strings and clears their pointers (0x0059D500; the destructor's tail call).
    void Clear_0059d500();

    char *ModemName;                    // +0x00
    char *ModemDeviceName;              // +0x04 the port to open
    char *ErrorCorrectionEnable;        // +0x08
    char *ErrorCorrectionDisable;       // +0x0C
    char *CompressionEnable;            // +0x10
    char *CompressionDisable;           // +0x14
    char *HardwareFlowControl;          // +0x18
};

// The serial frame header (6 bytes): then the data, an int CRC of the data
// (NullModemConnClass::Compute_CRC) and a carriage return.
struct SerialHeaderType {
    unsigned short MagicNumber;     // 0xDABD
    unsigned short Length;
    unsigned short MagicNumber2;    // 0xDEAF
};

// The CRC after a serial frame's data.
struct SerialCRCType {
    int SerialCRC;
};

// The serial frame overhead: the header and the CRC (unsigned, as the compares are).
#define PACKET_SERIAL_OVERHEAD_SIZE (sizeof(SerialHeaderType) + sizeof(SerialCRCType))

class NullModemConnClass : public ConnectionClass {
public:
    NullModemConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum);   // 0x005CDB40
    virtual ~NullModemConnClass();                                      // 0x005CDB90 (scalar deleting 0x005CDCD0 inlines it)
    void Init(int port);                                                // 0x005CDBB0
    virtual void Init();                                                // slot 1 0x005CDCC0
    virtual int Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id);   // slot 9 0x005CDBD0
    static int __fastcall Compute_CRC(char *buf, int buflen);           // 0x005CDC80 (rotating sum of the bytes)
    // The bytes a packet carries for the serial link: the frame header, the CRC and the queue header (0x005CDCB0).
    static int Packet_Overhead_Size();
    // A packet with its serial header, CRC and carriage return.
    int Actual_Max_Packet() { return MaxPacketLen + sizeof(SerialHeaderType) + sizeof(int) + sizeof(char); }

    int PortHandle;                     // +0x4C
    char *SendBuf;                      // +0x50
};

#include "shared/serial_settings.hpp"

// Waits the given ticks of the frame timer (0x00496A20; Red Alert's Delay).
void __fastcall Wait_Timer_00496A20(long ticks);

// The result of NullModemClass::Dial_Modem and Answer_Modem.
enum DialStatusType {
    DIAL_CONNECTED = 0,
    DIAL_NO_CARRIER,
    DIAL_BUSY,
    DIAL_ERROR,
    DIAL_NO_DIAL_TONE,
    DIAL_TIMEOUT,
    DIAL_CANCELED
};

// The modem command result names by status (0x007E78F0; NullMgr.CPP's debug log).
extern char ModemCmdNames[4][20];

// The modem's CONNECT line (0x00A72E10; Red Alert's ModemRXString).
extern char ModemRXString[80];

// ESC aborted the modem operation (0x00A72EC4).
extern bool unknown_modem_aborted_a72ec4;

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

    int Init(int port, int irq, char *dev_name, int baud, char parity, int wordlen, int stopbits);   // 0x005D00E0
    int Delete_Connection();                                            // 0x005D0360
    int Detect_Port(SerialSettingsType *settings);                      // 0x005D03E0 (0 when the port opens)
    int Init_Send_Queue();                                              // 0x005D03C0
    void Shutdown();                                                    // 0x005D0570
    int Send_Message(void *buf, int buflen, int ack_req);               // 0x005D05F0
    int Get_Message(void *buf, int *buflen);                            // 0x005D0630
    int Num_Send();                                                     // 0x005D08A0
    int Num_Receive();                                                  // 0x005D08C0
    void *Oldest_Send();                                                // 0x005D0920
    // Initialises the modem in failsafe mode under a dialog: echo, result codes, the
    // session's init string and the registry modem's options, auto-answer off (0x005D09A0).
    bool Detect_Modem(SerialSettingsType *settings, bool reconnect);
    // Dials string with method (tone or pulse) under a cancel dialog (0x005D1350).
    DialStatusType Dial_Modem(char *string, int method, bool reconnect);
    // Waits for a ring under a cancel dialog, answers with ATA and waits for the connection (0x005D16E0).
    DialStatusType Answer_Modem(bool reconnect);
    // Drops the line (DTR, escape code, ATH, ATZ): true when the modem answers (0x005D1B70).
    bool Hangup_Modem();
    void Setup_Modem_Echo(void (__fastcall *func)(char c));            // 0x005D1D20
    void unknown_5d1d40();                                              // 0x005D1D40 (empty)
    void Translate_Line_Ends();                                         // 0x005D1D50 (CR -> 1, LF -> 2 in the receive buffer)
    void Clear_Receive_Buffer();                                        // 0x005D1DA0
    int Get_Modem_Status();                                             // 0x005D1E50 (0x80: carrier detect)
    // Sends command plus terminator and reads the reply through SerialPort (no overall timeout; 0x005D1EA0).
    int Send_Modem_Command(char *command, char terminator, char *buffer, int buflen, int delay, int retries);
    static int Abort_Modem();                                           // 0x005D1DB0 (-1000 once ESC was pressed)
    void Setup_Abort_Modem();                                           // 0x005D1E00
    void Remove_Abort_Modem();                                          // 0x005D1E20
    int Change_IRQ_Priority(int irq);                                   // 0x005D1E40 (nothing to do under Windows: 0)
    int Number_Of(char *text);                                          // 0x005D1ED0 (atoi of an all-digit string, else -1)

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
    char *RXBuf;                        // +0x50 bytes read from the port
    int RXSize;                         // +0x54
    int RXCount;                        // +0x58
    unsigned long RetryDelta;           // +0x5C (60)
    unsigned long MaxRetries;           // +0x60 (-1)
    unsigned long Timeout;              // +0x64 (1200)
    unsigned long SendOverflows;        // +0x68
    unsigned long ReceiveOverflows;     // +0x6C
    unsigned long CRCErrors;            // +0x70
};

#endif
