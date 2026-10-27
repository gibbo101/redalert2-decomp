// WinsockInterfaceClass: the Winsock packet transport (_wsproto.cpp,
// 0x0076AA90-0x0076BE5F; vtable 0x007AFA7C, 23 slots), reached through
// PacketTransport (0x00839C50). Names follow the transport's debug
// strings where they say what a member does; the rest are hypotheses or
// unknown_. Slot signatures come from the bodies and the IPX callers.
//
// Layout (constructor 0x0076AC80, destructor 0x0076AD70):
//   +0x04  int (0x240)
//   +0x08, +0x20, +0x38  DynamicVectorClass<WinsockBufferType *> InBuffers,
//          OutBuffers, AltBuffers (growth 10)
//   +0x50, +0x15050, +0x2A050  WinsockBufferType Static*Buffers[128]
//   +0x3F050..+0x3F064  counters (+0x3F05C/60/64 static buffers in use)
//   +0x3F068  bool WinsockInitialised, +0x3F06C SOCKET Socket,
//   +0x3F070  SOCKET Socket2 (INVALID_SOCKET when closed)
//   +0x3F2F8  int (slot 20)
#ifndef RA2_SHARED_WINSOCK_INTERFACE_HPP
#define RA2_SHARED_WINSOCK_INTERFACE_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/keyboard.hpp"

WIN32_IMPORT BOOL WINAPI PostMessageA(void *window, unsigned int message, unsigned int wparam, long lparam);   // 0x0079A4A0

#include "shared/debug_printf.hpp"

// WSOCK32 entry points, called through their import thunks.
typedef unsigned int SOCKET;
#define INVALID_SOCKET ((SOCKET)(~0))
#define SOCKET_ERROR (-1)
extern "C" int __stdcall closesocket(SOCKET s);                                     // 0x00781B96
extern "C" int __stdcall WSAAsyncSelect(SOCKET s, void *window, unsigned int message, long events);   // 0x00781BC0
extern "C" int __stdcall WSAGetLastError();                                         // 0x00781B7E
extern "C" int __stdcall WSACleanup();                                              // 0x00781BBA
extern "C" int __stdcall getsockopt(SOCKET s, int level, int name, char *value, int *length);   // 0x00781B90
extern "C" int __stdcall setsockopt(SOCKET s, int level, int name, char const *value, int length);   // 0x00781BA8
extern "C" int __stdcall gethostname(char *name, int length);                       // 0x00781BD2
extern "C" int __stdcall WSAStartup(unsigned short version, void *data);            // 0x00781BCC
extern "C" int __stdcall EnumProtocolsA(int *protocols, void *buffer, unsigned long *length);   // 0x00781BC6
WIN32_IMPORT int WINAPI MessageBoxA(void *window, char const *text, char const *caption, unsigned int type);   // 0x0079A47C

// The start-up data block handed to WSAStartup (0x590 bytes allocated;
// only the version is read).
struct UnknownWinsockData {
    unsigned short wVersion;            // +0x00
    char unknown_02[0x590 - 2];
};

// One EnumProtocols entry (Winsock 1.1 PROTOCOL_INFO, 32 bytes).
struct UnknownProtocolInfo {
    unsigned long dwServiceFlags;
    int iAddressFamily;
    int iMaxSockAddr;
    int iMinSockAddr;
    int iSocketType;
    int iProtocol;
    unsigned long dwMessageSize;        // +0x18
    char *lpProtocol;                   // +0x1C
};

// Folds a word into a rotating checksum (0x0062A340).
void __fastcall Add_CRC(unsigned long *crc, unsigned long value);

// The window that receives the socket notifications (0x00B263D8).
extern void *unknown_window_b263d8;

class WinsockInterfaceClass {
public:
    // A packet buffer (0x2A0 bytes).
    class WinsockBufferType {
    public:
        unsigned char Address[16];      // +0x00 the peer's socket address
        int BufferLen;                  // +0x10
        bool IsBroadcast;               // +0x14
        bool InUse;                     // +0x15 (a static buffer taken)
        bool IsAllocated;               // +0x16 (allocated rather than static)
        bool IsAlternate;               // +0x17 (from the alternate pool/socket)
        unsigned char unknown_18;       // +0x18
        unsigned short unknown_1a;      // +0x1A
        unsigned long CRC;              // +0x1C
        char Buffer[0x280];             // +0x20
    };

    WinsockInterfaceClass();                                            // 0x0076AC80
    virtual ~WinsockInterfaceClass();                                   // 0x0076AD70
    virtual void Close_Socket();                                        // slot 1 0x0076AE40
    virtual int unknown_slot2(void *buf, int *buflen, void *address, int *addresslen, unsigned short *port);   // slot 2 0x0076B5A0 (takes the oldest incoming packet)
    virtual void unknown_slot3(void *buf, int buflen, void *address, int addresslen, bool alternate, unsigned char arg6, unsigned short arg7);   // slot 3 0x0076B670 (queues a write to an address, posts FD_WRITE)
    virtual void unknown_slot4(void *buf, int buflen, bool alternate);  // slot 4 0x0076B7A0 (queues a broadcast, posts FD_WRITE)
    virtual void Discard_In_Buffers();                                  // slot 5 0x0076AF60
    virtual void Discard_Out_Buffers();                                 // slot 6 0x0076AFD0
    virtual bool Start_Listening();                                     // slot 7 0x0076AE80
    virtual void Stop_Listening();                                      // slot 8 0x0076AF10
    virtual void Clear_Socket_Error(SOCKET socket);                     // slot 9 0x0076B8A0
    virtual bool Set_Socket_Options(SOCKET socket);                     // slot 10 0x0076B8F0
    virtual void unknown_slot11(char *address, unsigned short port) {}  // slot 11 0x0076AA00 (inline; UDP: adds a broadcast address)
    virtual void unknown_slot12() {}                                    // slot 12 0x0076AA10 (inline)
    virtual int unknown_slot13() { return 0; }                          // slot 13 0x0076BA00 (inline)
    virtual unsigned int unknown_slot14(int socket) { return 0; }       // slot 14 0x0076BA10 (inline; the notification message)
    virtual bool unknown_slot15(int socket) { return false; }           // slot 15 0x0076BA20 (inline; opens a socket)
    virtual int unknown_slot16(int arg1, int arg2, int arg3, int arg4) { return 1; }   // slot 16 0x0076BA30 (inline)
    virtual bool Get_Host_Name(char *name, int length);                 // slot 17 0x0076B990
    virtual int unknown_slot18() { return 0; }                          // slot 18 0x0076AA20 (inline)
    virtual int unknown_slot19(int arg1) { return 0; }                  // slot 19 0x0076AA30 (inline)
    virtual void unknown_slot20(int arg1) { unknown_3f2f8 = arg1; }     // slot 20 0x0076AA40 (inline)
    virtual void Build_Packet_CRC(WinsockBufferType *packet);           // slot 21 0x0076B290
    virtual bool Passes_CRC_Check(WinsockBufferType *packet);           // slot 22 0x0076B310

    void Close();                                                       // 0x0076AE10
    WinsockBufferType *Get_New_Out_Buffer(bool alternate);              // 0x0076B3A0
    WinsockBufferType *Get_New_In_Buffer();                             // 0x0076B500
    bool Init();                                                        // 0x0076B0A0

    static void __fastcall unknown_76b9e0(int value);   // 0x0076B9E0 (sets unknown_b2aea0)
    static int unknown_76b9f0();                        // 0x0076B9F0 (reads it)
    static int unknown_b2aea0;          // 0x00B2AEA0 (packet loss simulation when positive)
    static bool unknown_b2ae9c;         // 0x00B2AE9C (its warning was shown)
    static int Protocols[];             // 0x00800AB0 (17 UDP, 1000 IPX, 0)
    static int SocketReceiveBuffer;     // 0x00800AC0 (0x20000)
    static int SocketSendBuffer;        // 0x00800ABC (0x20000)

    int unknown_04;                                     // +0x04
    DynamicVectorClass<WinsockBufferType *> InBuffers;  // +0x08
    DynamicVectorClass<WinsockBufferType *> OutBuffers; // +0x20
    DynamicVectorClass<WinsockBufferType *> AltBuffers; // +0x38
    WinsockBufferType StaticInBuffers[128];             // +0x50
    WinsockBufferType StaticOutBuffers[128];            // +0x15050
    WinsockBufferType StaticAltBuffers[128];            // +0x2A050
    int NextInBuffer;                                   // +0x3F050 (next static buffer to try)
    int NextOutBuffer;                                  // +0x3F054
    int NextAltBuffer;                                  // +0x3F058
    int StaticInBuffersInUse;                           // +0x3F05C
    int StaticOutBuffersInUse;                          // +0x3F060
    int StaticAltBuffersInUse;                          // +0x3F064
    bool WinsockInitialised;                            // +0x3F068
    SOCKET Socket;                                      // +0x3F06C
    SOCKET Socket2;                                     // +0x3F070
    char unknown_3f074[0x3F2F8 - 0x3F074];
    int unknown_3f2f8;                                  // +0x3F2F8
};

// The active transport (0x00839C50).
extern WinsockInterfaceClass *PacketTransport;
// The value the IPX code hands transport slot 20 first (0x00A40B60).
extern int unknown_a40b60;

#endif
