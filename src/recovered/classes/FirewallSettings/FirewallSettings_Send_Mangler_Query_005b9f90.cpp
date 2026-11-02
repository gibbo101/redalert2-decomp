// bool FirewallSettings::Send_Mangler_Query(IPXAddressClass *address, unsigned short port, int packet_id, bool flag)
// (0x005B9F90): selects port on the UDP transport, sends a 0x2B mangler query ("WW", the port, flag) to address as a
// global message and services the manager until it has gone out (180 ticks at most), then resets the port.
#include "shared/firewall_settings.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/udp_interface.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"
void unknown_481fb0();
// @ref ?unknown_481fb0@@YAXXZ=00481fb0
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ??_C@_02PIAM@WW?$AA@=007e641c
// @ref ??_C@_0BM@OCAO@Sending?5from?5port?5?$CFd?5to?5?$CFs?6?$AA@=007e6400

bool FirewallSettings::Send_Mangler_Query(IPXAddressClass *address, unsigned short port, int packet_id, bool flag)
{
    char buffer[456];
    ManglerPacket &packet = *(ManglerPacket *)buffer;
    packet.Type = 0x2B;
    strcpy(packet.Name, "WW");
    ((UDPInterfaceClass *)PacketTransport)->unknown_slot29(port);
    packet.Port = port;
    packet.unknown_37 = (flag == true);
    int count = unknown_ipx_manager_a40978.Global_Num_Send();
    Debug_Printf("Sending from port %d to %s\n", port, address->As_String_00523840());
    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, address, *(unsigned short *)address, packet_id);
    CDTimerClass<SystemTimerClass> timer(180);
    while (unknown_ipx_manager_a40978.Global_Num_Send() > count || PacketTransport->OutBuffers.Count()) {
        if (!timer) {
            break;
        }
        unknown_ipx_manager_a40978.Service();
        unknown_481fb0();
    }
    ((UDPInterfaceClass *)PacketTransport)->unknown_slot29(0);
    return true;
}
