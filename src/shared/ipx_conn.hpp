// IPXConnClass: a ConnectionClass to one IPX address (ipxconn.cpp,
// 0x00523980-0x00523FB1; vtable 0x007A4644, slot 10 Send_To new) and the
// IPX address it uses. Names follow Westwood's IPX connection (hypotheses).
//
// Layout (constructor 0x00523B70):
//   +0x4C  IPXAddressClass Address, +0x58 NetNodeType ImmediateAddress,
//   +0x60  int (0), +0x64 int ID, +0x68 char Name[]
#ifndef RA2_SHARED_IPX_CONN_HPP
#define RA2_SHARED_IPX_CONN_HPP

#include "shared/connection.hpp"
#include "shared/winsock_interface.hpp"

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);    // 0x00783689

#include "shared/ipx_address.hpp"

// The forwarding route (game mode 4 with unknown_flag_a3fba8): the address
// and port packets are forwarded through, the address it is compared with
// (the first session node) and the port a forwarded header carries.
extern IPXAddressClass unknown_forward_address_a3fbac;   // 0x00A3FBAC
extern IPXAddressClass unknown_forward_address_a3fbb8;   // 0x00A3FBB8
extern int unknown_forward_port_a3fbc4;                   // 0x00A3FBC4
extern int unknown_port_7f60dc;                           // 0x007F60DC

class IPXConnClass : public ConnectionClass {
public:
    IPXConnClass(int numsend, int numreceive, int maxlen, unsigned short magicnum,
        IPXAddressClass *address, int id, wchar_t const *name, int extralen = 0);    // 0x00523B70
    virtual ~IPXConnClass() {}                                      // inline (scalar deleting destructor 0x00523F90)
    virtual void Init();                                            // slot 1 0x00523C20
    virtual int Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id);   // slot 9 0x00523D10
    virtual int Send_To(char *buf, int buflen, IPXAddressClass *address, unsigned char *immed, bool flagged, unsigned short id);   // slot 10 0x00523D90

    static void __fastcall Configure(unsigned short socket, int conn_num, int arg3, int arg4, int arg5, int arg6, int arg7);   // 0x00523C30
    static int Start_Listening();                                   // 0x00523C80
    static int Stop_Listening();                                    // 0x00523CF0
    static void __fastcall Open_Socket(unsigned short socket);      // 0x00523D30
    static void Close_Socket();                                     // 0x00523D70
    static int __fastcall Broadcast(char *buf, int buflen);         // 0x00523F70

    IPXAddressClass Address;            // +0x4C
    NetNodeType ImmediateAddress;       // +0x58
    int unknown_60;                     // +0x60
    int ID;                             // +0x64
    wchar_t Name[40];                   // +0x68 (to +0xB8, where IPXGlobalConnClass starts; length a hypothesis)

    static int unknown_a52370;          // 0x00A52370 (Configure's sixth argument)
    static int unknown_a52398;          // 0x00A52398 (fifth)
    static int ConnectionNum;           // 0x00A523B0
    static int unknown_a523c4;          // 0x00A523C4 (third)
    static unsigned short Socket;       // 0x00A523D0
    static int unknown_a523d4;          // 0x00A523D4 (seventh)
    static int unknown_a523e0;          // 0x00A523E0 (fourth)
    static int Configured;              // 0x00A52404
    static int SocketOpen;              // 0x00A52408
    static int Listening;               // 0x00A5240C
};

#endif
