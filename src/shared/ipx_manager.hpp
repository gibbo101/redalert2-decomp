// ConnManClass (the abstract connection manager, vtable 0x007A474C, 16
// slots) and IPXManagerClass (ipxmgr.cpp, 0x00524E40-0x0052788D; vtable
// 0x007A46E4, 25 slots). Slot names follow Westwood's connection manager
// where the behaviour agrees (hypotheses); the rest stay unknown_slotN.
//
// IPXManagerClass layout (constructor 0x00525030, destructor 0x00525130):
//   +0x04  bool IPXStatus (a transport could be initialised), +0x05 bool Listening
//   +0x08  Glb_MaxPacketLen, +0x0C Glb_NumPackets, +0x10 Pvt_MaxPacketLen,
//   +0x14  Pvt_NumPackets, +0x18/+0x1C the second global channel's
//          packet length and count
//   +0x20  unsigned short ProductID, +0x22 unsigned short Socket (byte-swapped)
//   +0x24  int ConnectionNum
//   +0x28  IPXConnClass *Connection[7], +0x44 int NumConnections
//   +0x48  IPXGlobalConnClass *GlobalChannel, +0x4C a second global
//          channel (magic 0xCDEF), +0x50 IPXConnClass * the multicast
//          connection, +0x54 int CurConnection
//   +0x58  RetryDelta, +0x5C MaxRetries, +0x60 Timeout
//   +0x64..+0x6C  saved global-channel timing
//   +0x74..+0x98  values handed to IPXConnClass::Configure
//   +0xA0  SendOverflows, +0xA4 int, +0xA8 int (-1)
#ifndef RA2_SHARED_IPX_MANAGER_HPP
#define RA2_SHARED_IPX_MANAGER_HPP

#include "shared/ipx_global_conn.hpp"
#include "shared/ipx_interface.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/conn_man.hpp"
#include "shared/unknown_player_entry.hpp"

enum {
    CONNECT_MAX = 7
};

// The session players: 0x00A3FA7C is the list of NodeNameType (shared/unknown_player_entry.hpp).
// A per-node unsigned short, by node index (0x00A402BA).
extern unsigned short unknown_node_ids_a402ba[];

extern "C" int __cdecl _wcsicmp(wchar_t const *string1, wchar_t const *string2);   // 0x00796318

// The frames-ahead value the timing printout reports (0x00A3D560).
extern int unknown_max_ahead_a3d560;

// An ASCII string widened into a rotating static buffer (0x006FA180).
wchar_t *__fastcall Unknown_006FA180(char const *text);


class IPXManagerClass : public ConnManClass {
public:
    IPXManagerClass(int glb_maxlen, int pvt_maxlen, int glb_num_packets, int pvt_num_packets,
        unsigned short socket, unsigned short product_id);             // 0x00525030
    virtual ~IPXManagerClass();                                         // 0x00525130

    int Init();                                                         // 0x005251C0
    int Is_IPX();                                                       // 0x00525390
    int Create_Connection(int id, wchar_t const *name, IPXAddressClass *address);   // 0x00525500
    int unknown_5255b0();                                               // 0x005255B0 (creates the multicast connection)
    int Delete_Connection(int id);                                      // 0x00525640
    wchar_t *Connection_Name(int id);                                   // 0x00525700
    IPXAddressClass *Connection_Address(int id);                        // 0x00525740
    void unknown_525800(int index, int id, wchar_t const *name);        // 0x00525800 (renames a connection)
    int Send_Global_Message(void *buf, int buflen, int ack_req, IPXAddressClass *address, unsigned short id, unsigned long packet_id);   // 0x00525830
    int unknown_5258b0(void *buf, int buflen, int ack_req, int node_id);           // 0x005258B0 (to a node by ID)
    int unknown_5259a0(void *buf, int buflen, int ack_req, wchar_t const *name);   // 0x005259A0 (to a node by name)
    int Get_Global_Message(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id);   // 0x00525AB0
    int unknown_525af0(int index, void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id, unsigned long *packet_id);   // 0x00525AF0
    void unknown_525b30(int index);                                     // 0x00525B30
    int unknown_525b50(void *buf, int buflen, bool ack_req);            // 0x00525B50 (on the second global channel)
    int unknown_525bc0(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id);   // 0x00525BC0
    void Set_Connection_Address(int id, IPXAddressClass *address);      // 0x005269F0
    int unknown_526a30();                                               // 0x00526A30
    void Set_Socket(unsigned short socket);                             // 0x00526BA0
    unsigned long unknown_526c30();                                     // 0x00526C30 (global channel's mean delay)
    unsigned long unknown_526c50();                                     // 0x00526C50 (second global channel's)
    unsigned long unknown_526c70();                                     // 0x00526C70 (multicast connection's)
    char *unknown_5276a0();                                             // 0x005276A0 (the oldest unacknowledged sequenced send)
    void Set_Bridge(NetNumType bridge);                                 // 0x00527730 (Red Alert's Set_Bridge)
    void unknown_5277c0(IPXAddressClass *address);                      // 0x005277C0
    void unknown_5277f0();                                              // 0x005277F0
    void unknown_527800();                                              // 0x00527800
    void unknown_527810(IPXAddressClass *address, unsigned short id);   // 0x00527810
    void unknown_527830(int index);                                     // 0x00527830

    virtual int Service();                                              // 1 0x00525F60
    virtual int Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id);   // 2 0x00525C00
    virtual int Get_Private_Message(void *buf, int *buflen, int *conn_id);   // 3 0x00525D30
    virtual int Num_Connections();                                      // 4 0x005256D0
    virtual int Connection_ID(int index);                               // 5 0x005256E0
    virtual int Connection_Index(int id);                               // 6 0x00525780
    virtual int Global_Num_Send();                                      // 7 0x00526A40
    virtual int Global_Num_Receive();                                   // 8 0x00526A60
    virtual int Private_Num_Send(int id);                               // 9 0x00526AC0
    virtual int Private_Num_Receive(int id);                            // 10 0x00526B30
    virtual void Reset_Response_Time(bool clear);                       // 11 0x00527630
    virtual unsigned long Response_Time();                              // 12 0x00526BC0
    virtual void Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global);   // 13 0x005253A0
    virtual void unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout);   // 14 0x00525450 (the global channel's timing)
    virtual void Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount);   // 15 0x00527750
    virtual void unknown_slot16();                                      // 16 0x00525480 (saves the global channel's timing)
    virtual void unknown_slot17();                                      // 17 0x005254A0 (restores it)
    virtual void unknown_slot18(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout);   // 18 0x005254C0 (the other channels' timing)
    virtual int unknown_slot19(ConnectionClass *connection);            // 19 0x005257B0 (index, or -2/-3/-4 for the channels)
    virtual int unknown_slot20();                                       // 20 0x00526A80 (second global channel: queued sends)
    virtual int unknown_slot21();                                       // 21 0x00526AA0 (and receives)
    virtual unsigned long unknown_slot22(int index);                    // 22 0x00526C10 (a connection's mean delay)
    virtual int unknown_slot23();                                       // 23 0x00526C90
    virtual void Mono_Debug_Print(int index, int refresh) {}            // 24 0x005277B0 (empty; inline)

    bool IPXStatus;                     // +0x04
    bool Listening;                     // +0x05
    int Glb_MaxPacketLen;               // +0x08
    int Glb_NumPackets;                 // +0x0C
    int Pvt_MaxPacketLen;               // +0x10
    int Pvt_NumPackets;                 // +0x14
    int unknown_18;                     // +0x18
    int unknown_1c;                     // +0x1C
    unsigned short ProductID;           // +0x20
    unsigned short Socket;              // +0x22
    int ConnectionNum;                  // +0x24
    IPXConnClass *Connection[CONNECT_MAX];  // +0x28
    int NumConnections;                 // +0x44
    IPXGlobalConnClass *GlobalChannel;  // +0x48
    IPXGlobalConnClass *unknown_4c;     // +0x4C
    IPXConnClass *unknown_50;           // +0x50
    int CurConnection;                  // +0x54
    unsigned long RetryDelta;           // +0x58
    unsigned long MaxRetries;           // +0x5C
    unsigned long Timeout;              // +0x60
    unsigned long unknown_64;           // +0x64
    unsigned long unknown_68;           // +0x68
    unsigned long unknown_6c;           // +0x6C
    int unknown_70;                     // +0x70
    int unknown_74;                     // +0x74
    int unknown_78;                     // +0x78
    int unknown_7c;                     // +0x7C
    int unknown_80;                     // +0x80
    char unknown_84[0x94 - 0x84];
    int unknown_94;                     // +0x94
    int unknown_98;                     // +0x98
    int unknown_9c;                     // +0x9C
    int SendOverflows;                  // +0xA0
    int unknown_a4;                     // +0xA4
    int unknown_a8;                     // +0xA8
};

// The game's IPX manager (0x00A40978; defined in the IPXManagerClass unit).
extern IPXManagerClass unknown_ipx_manager_a40978;
// The destination network address set from [Network] DestNet (0x00A3F608) and
// the flag that it is set (0x00A3F604; OptionsClass, name hypotheses).
extern int unknown_dest_net_set_a3f604;
extern IPXAddressClass unknown_dest_net_a3f608;

#endif
