// unsigned short FirewallSettings::Get_Mangled_Port(unsigned short port) (0x005BAF50; called from 0x0074E87B):
// the port a NAT will map port to. Types 0 and odd types return port. Otherwise resolves the mangler (servserv's
// current entry, else mangler1.westwood.com:4321), and for sequential NATs (type & 4) opens the next pool port
// (Get_Next_Port inlined); queries the mangler from it for up to 180 ticks and predicts the mapping from the
// reply and the allocation delta (+0x08): delta 100 relative, else the next delta boundary plus port % delta,
// or reply + delta for type & 0x10; wrapped into 0x400..0xFFFF.
#include "shared/firewall_settings.hpp"
#include "shared/ipx_address.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/udp_interface.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"
// @ref ??_C@_0BG@MLDE@mangler1?4westwood?4com?$AA@=007e6918
// @ref ??_C@_0BH@BBKO@Mangler?5address?5is?5?$CFs?6?$AA@=007e68a0
// @ref ??_C@_0BN@JACA@Using?5mangler?5from?5servserv?6?$AA@=007e65a4
// @ref ??_C@_0CE@LLMM@FirewallHelper?5?9?5Mangled?5port?5?$DN?5@=007e6840
// @ref ??_C@_0CF@LNBH@Mangler?5address?5is?5?$CFd?4?$CFd?4?$CFd?4?$CFd?5?$DL@=007e68b8
// @ref ??_C@_0CP@BKLK@FirewallHelper?5?9?5Getting?5manglin@=007e6864
// @ref ??_C@_0DD@LEJG@Couldn?8t?5find?5mangled?5port?0?5retu@=007e680c
// @ref ??_C@_0DE@CNHK@FirewallHelper?5?9?5Returning?5next?5@=007e67d8
// @ref ??_C@_0DG@OIGL@Firewall?5helper?5?9?5About?5to?5call?5@=007e68e0
// @ref ??_C@_0L@HLJL@fw?5?$DN?5?$CF08x?6?$AA@=007e6894
// @ref ?unknown_mangler_count_b2ac34@@3HA=00b2ac34
// @ref ?unknown_mangler_index_b2ac38@@3HA=00b2ac38
// @ref ?unknown_mangler_addresses_b26cbc@@3PAY0IA@DA=00b26cbc
// @ref ?unknown_mangler_ports_b291a4@@3PAHA=00b291a4
// @ref ?unknown_mangler_packet_id_7e63d4@@3HA=007e63d4
// @ref ??_C@_0CF@NPCK@gethostbyname?5failed?$CB?5Error?5code@=007e6554
// @ref _gethostbyname@4=00781b84
// @ref _WSAGetLastError@0=00781b7e
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// The servserv mangler list (declared in wol_sink.hpp, whose WOL templates this unit does not emit).
extern int unknown_mangler_count_b2ac34;
extern int unknown_mangler_index_b2ac38;
extern char unknown_mangler_addresses_b26cbc[64][128];
extern int unknown_mangler_ports_b291a4[64];
extern int unknown_mangler_packet_id_7e63d4;    // 0x007E63D4 the next mangler query id

unsigned short FirewallSettings::Get_Mangled_Port(unsigned short port)
{
    CDTimerClass<SystemTimerClass> timer;
    int type = unknown_00;
    if (type == 0) {
        return port;
    }
    if (type & 1) {
        return port;
    }
    char hostname[256];
    unsigned short mangler_port = 0x10E1;
    strcpy(hostname, "mangler1.westwood.com");
    if (unknown_mangler_count_b2ac34 > 0) {
        strcpy(hostname, unknown_mangler_addresses_b26cbc[unknown_mangler_index_b2ac38]);
        mangler_port = unknown_mangler_ports_b291a4[unknown_mangler_index_b2ac38];
        Debug_Printf("Using mangler from servserv\n");
    }
    Debug_Printf("Firewall helper - About to call gethostbyname for %s\n", hostname);
    hostent *host = gethostbyname(hostname);
    if (host == 0) {
        Debug_Printf("gethostbyname failed! Error code %d\n", WSAGetLastError());
        return port;
    }
    unsigned long ip = *(unsigned long *)host->h_addr_list[0];
    Debug_Printf("Mangler address is %d.%d.%d.%d ; %d\n",
        ((unsigned char *)&ip)[0], ((unsigned char *)&ip)[1], ((unsigned char *)&ip)[2], ((unsigned char *)&ip)[3], mangler_port);
    IPXAddressClass address;
    address.Set_Node((unsigned char *)&ip);
    address.unknown_523960(mangler_port);
    Debug_Printf("Mangler address is %s\n", address.As_String_00523840());
    unsigned short source = 0;
    unsigned short opened = 0;
    Debug_Printf("fw = %08x\n", type);
    int sequential = type & 4;
    if (sequential) {
        source = Get_Next_Port(1);
        opened = source;
        if (!((UDPInterfaceClass *)PacketTransport)->Open_Spare_Socket(opened)) {
            return port;
        }
        PacketTransport->Start_Listening();
    }
    Debug_Printf("FirewallHelper - Getting mangling for port %d\n", source);
    timer = CDTimerClass<SystemTimerClass>(180);
    unsigned short mangled = 0;
    while (timer && !mangled) {
        Send_Mangler_Query(&address, source, unknown_mangler_packet_id_7e63d4, false);
        mangled = Wait_For_Mangler_Reply(unknown_mangler_packet_id_7e63d4, 30);
        Debug_Printf("FirewallHelper - Mangled port = %d\n", mangled);
    }
    unknown_mangler_packet_id_7e63d4++;
    if (opened) {
        ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(opened);
    }
    if (!mangled) {
        Debug_Printf("Couldn't find mangled port, returning source port\n");
        return port;
    }
    if (!sequential) {
        Debug_Printf("FirewallHelper - Returning next mangled port as %d\n", mangled);
        return mangled;
    }
    int result;
    if (type & 0x10) {
        result = unknown_08 + mangled;
    } else {
        int delta = unknown_08;
        if (delta == 100) {
            result = mangled - source + port + 100;
        } else {
            result = (mangled / delta + 1) * delta + port % delta;
        }
    }
    if (result > 0xFFFF) {
        result -= 0xFFFF;
    }
    if (result < 0x400) {
        result += 0x400;
    }
    Debug_Printf("FirewallHelper - Returning next mangled port as %d\n", result);
    return result;
}
