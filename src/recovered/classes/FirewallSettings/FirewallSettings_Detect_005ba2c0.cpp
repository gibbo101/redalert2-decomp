// int FirewallSettings::Detect_005ba2c0(bool *found) (0x005BA2C0): the NAT/firewall detection. A source port
// given by the user skips it (type 1, or 9 with the Netgear bug flag). Otherwise resolves up to four distinct
// mangler addresses (servserv's list, else the defaults; at least three needed), checks whether two queries from
// one port come back with the same or different ports, then queries four fresh ports up to three times and
// derives the allocation delta (relative or absolute, sequential sets *found), and for sequential NATs tests
// whether a second destination port at the same address is mangled differently.
#include "shared/firewall_settings.hpp"
#include "shared/ipx_address.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/udp_interface.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ?unknown_source_port_a4025c@@3HA=00a4025c
// @ref ?unknown_netgear_bug_a40188@@3_NA=00a40188
// @ref ?unknown_router_b2ac30@@3HA=00b2ac30
// @ref ?unknown_mangler_count_b2ac34@@3HA=00b2ac34
// @ref ?unknown_mangler_addresses_b26cbc@@3PAY0IA@DA=00b26cbc
// @ref ?unknown_mangler_ports_b291a4@@3PAHA=00b291a4
// @ref ?unknown_default_manglers_7e6334@@3PAY0CA@DA=007e6334
// @ref _gethostbyname@4=00781b84
// @ref _WSAGetLastError@0=00781b7e
// @ref ??_C@_0BJ@BLDP@Testing?5for?5Netgear?5bug?6?$AA@=007e64a0
// @ref ??_C@_0BN@JACA@Using?5mangler?5from?5servserv?6?$AA@=007e65a4
// @ref ??_C@_0CC@IKGL@Source?5port?5?$CFd?5specified?5by?5user@=007e6638
// @ref ??_C@_0CG@GEGA@Found?5mangler?5address?5at?5?$CFd?4?$CFd?4?$CF@=007e657c
// @ref ??_C@_0DF@KLHC@About?5to?5call?5gethostbyname?5for?5@=007e65c4
// @ref ??_C@_0DJ@CHII@Netgear?5bug?5specified?5by?5command@=007e65fc
// @ref ??_C@_0DP@JKOA@NAT?5uses?5the?5same?5source?5port?5fo@=007e6460
// @ref ??_C@_0EB@IJDC@NAT?5uses?5different?5source?5ports?5@=007e64bc
// @ref ??_C@_0FD@KGBG@Testing?5to?5see?5if?5the?5NAT?5mangle@=007e6500
// @ref ??_C@_0CF@NPCK@gethostbyname?5failed?$CB?5Error?5code@=007e6554
extern int unknown_source_port_a4025c;          // 0x00A4025C the source port given by the user
extern bool unknown_netgear_bug_a40188;         // 0x00A40188 Netgear bug flag (command line or SendDelay)
extern int unknown_router_b2ac30;               // 0x00B2AC30
extern int unknown_mangler_count_b2ac34;
extern char unknown_mangler_addresses_b26cbc[64][128];
extern int unknown_mangler_ports_b291a4[64];
extern char unknown_default_manglers_7e6334[][32];

int FirewallSettings::Detect_005ba2c0(bool *found)
{
    unsigned short mangler_port = 0x10E1;
    int packet_id = 0x7F000000;
    *found = false;
    int count = 0;
    IPXAddressClass addresses[4];
    CDTimerClass<SystemTimerClass> timer;
    unsigned short sources[4];
    unsigned short mangled[4];
    bool relative;
    bool sequential;

    if (unknown_source_port_a4025c != 0) {
        int type = 1;
        Debug_Printf("Source port %d specified by user\n", unknown_source_port_a4025c);
        if (unknown_netgear_bug_a40188) {
            type = 9;
            Debug_Printf("Netgear bug specified by command line or SendDelay flag\n");
        }
        return type;
    }

    timer = CDTimerClass<SystemTimerClass>(300);
    Debug_Printf("About to call gethostbyname for the mangler address\n");
    unsigned long ips[4];
    int i = 0;
    do {
        char const *name = unknown_default_manglers_7e6334[i];
        if (unknown_mangler_count_b2ac34 > i) {
            name = unknown_mangler_addresses_b26cbc[i];
            mangler_port = unknown_mangler_ports_b291a4[i];
            Debug_Printf("Using mangler from servserv\n");
        }
        i++;
        if (strlen(name) == 0) {
            break;
        }
        char hostname[256];
        strcpy(hostname, name);
        hostent *host = gethostbyname(hostname);
        if (host == 0) {
            Debug_Printf("gethostbyname failed! Error code %d\n", WSAGetLastError());
            break;
        }
        bool dup = false;
        for (int j = 0; j < count; j++) {
            if (memcmp(&ips[j], host->h_addr_list[0], 4) == 0) {
                dup = true;
                break;
            }
        }
        if (!dup) {
            int n = count++;
            ips[n] = *(unsigned long *)host->h_addr_list[0];
            Debug_Printf("Found mangler address at %d.%d.%d.%d\n",
                ((unsigned char *)&ips[n])[0], ((unsigned char *)&ips[n])[1], ((unsigned char *)&ips[n])[2], ((unsigned char *)&ips[n])[3]);
        }
    } while (count < 4 && timer);

    if (count < 3) {
        return 1;
    }
    for (int k = 0; k < count; k++) {
        NetNodeType node;
        *(unsigned long *)node = ips[k];
        addresses[k].Set_Node(node);
        addresses[k].unknown_523960(mangler_port);
    }

    unsigned short port = Get_Next_Port(1);
    if (!((UDPInterfaceClass *)PacketTransport)->Open_Spare_Socket(port)) {
        return 1;
    }
    PacketTransport->Start_Listening();

    timer = CDTimerClass<SystemTimerClass>(360);
    unsigned short reply1 = 0;
    while (timer && !reply1) {
        Send_Mangler_Query(&addresses[0], port, 0x7F000000, false);
        reply1 = Wait_For_Mangler_Reply(0x7F000000, 0);
    }
    if (reply1 == 0 || reply1 == port) {
        ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(port);
        if (reply1 == port) {
            unknown_08 = 0;
            *found = true;
        }
        return 1;
    }

    timer = CDTimerClass<SystemTimerClass>(360);
    unsigned short reply2 = 0;
    while (timer && !reply2) {
        Send_Mangler_Query(&addresses[1], port, 0x7F000001, false);
        reply2 = Wait_For_Mangler_Reply(0x7F000001, 0);
    }
    ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(port);
    if (reply2 == 0 || reply2 == port) {
        return 1;
    }

    int result = (reply1 != reply2) ? 4 : 2;
    int j;
    for (int attempt = 0; attempt < 3; attempt++) {
        memset(sources, 0, sizeof(sources));
        memset(mangled, 0, sizeof(mangled));
        for (j = 0; j < 4; j++) {
            sources[j] = Get_Next_Port(j);
            if (!((UDPInterfaceClass *)PacketTransport)->Open_Spare_Socket(sources[j])) {
                for (int c = 0; c < j; c++) {
                    if (sources[c]) {
                        ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(sources[c]);
                    }
                }
                return result;
            }
        }
        PacketTransport->Start_Listening();
        packet_id += 10;
        int replies = 0;
        timer = CDTimerClass<SystemTimerClass>(720);
        while (timer && replies < 4) {
            for (j = 0; j < 4; j++) {
                if (mangled[j] == 0) {
                    Send_Mangler_Query(&addresses[0], sources[j], packet_id + j, false);
                    mangled[j] = Wait_For_Mangler_Reply(packet_id + j, 0);
                    if (mangled[j]) {
                        replies++;
                    }
                }
            }
        }
        for (int c = 0; c < j; c++) {
            if (sources[c]) {
                ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(sources[c]);
            }
        }
        if (replies < 4) {
            if (unknown_0c && unknown_04 > 1) {
                unknown_08 = unknown_0c;
            }
            return result;
        }
        relative = false;
        sequential = false;
        int delta = Get_Allocation_Delta(replies, sources, mangled, &relative, &sequential);
        if (delta) {
            int kind;
            if (relative) {
                kind = 0x20;
            } else {
                kind = 0x10;
            }
            result |= kind;
            unknown_08 = delta;
            if (sequential) {
                *found = true;
            }
            break;
        }
        if (unknown_0c && unknown_04 > 1) {
            unknown_08 = unknown_0c;
        }
    }

    if (result & 4) {
        if (result & 0x10) {
            Debug_Printf("Testing to see if the NAT mangles differently per destination port at the same IP\n");
            unsigned short port_a = Get_Next_Port(1);
            if (!((UDPInterfaceClass *)PacketTransport)->Open_Spare_Socket(port_a)) {
                return result;
            }
            unsigned short port_b = Get_Next_Port(1);
            if (!((UDPInterfaceClass *)PacketTransport)->Open_Spare_Socket(port_b)) {
                return result;
            }
            PacketTransport->Start_Listening();
            timer = CDTimerClass<SystemTimerClass>(240);
            unsigned short reply_a = 0;
            packet_id++;
            while (timer && !reply_a) {
                Send_Mangler_Query(&addresses[0], port_a, packet_id, false);
                reply_a = Wait_For_Mangler_Reply(packet_id, 0);
            }
            if (!reply_a) {
                ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(port_a);
                ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(port_b);
                return result;
            }
            IPXAddressClass other = addresses[0];
            other.unknown_523960(*(unsigned short *)other.NetworkNumber + 1);
            Send_Mangler_Query(&other, port_a, packet_id, false);
            Send_Mangler_Query(&other, port_a, packet_id, false);
            Send_Mangler_Query(&other, port_a, packet_id, false);
            packet_id++;
            unsigned short reply_b = 0;
            timer = CDTimerClass<SystemTimerClass>(240);
            while (timer && !reply_b) {
                Send_Mangler_Query(&addresses[0], port_b, packet_id, false);
                reply_b = Wait_For_Mangler_Reply(packet_id, 0);
            }
            if (reply_b) {
                if (reply_b != reply_a + unknown_08) {
                    Debug_Printf("NAT uses different source ports for different destination ports\n");
                    result |= 0x40;
                } else {
                    Debug_Printf("NAT uses the same source port for different destination ports\n");
                }
            }
        } else {
            result |= 0x40;
        }
    }
    Debug_Printf("Testing for Netgear bug\n");
    if (unknown_router_b2ac30 == 2 || unknown_netgear_bug_a40188) {
        result |= 8;
        Debug_Printf("Netgear bug specified by command line or SendDelay flag\n");
    }
    return result;
}
