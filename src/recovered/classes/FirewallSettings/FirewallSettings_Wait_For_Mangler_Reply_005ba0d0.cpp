// unsigned short FirewallSettings::Wait_For_Mangler_Reply(int packet_id, int time) (0x005BA0D0): services the manager
// for 60 ticks (or time) looking for the mangler's 0x2C reply to packet_id (product 0xAA03); returns the port the
// mangler saw ("Mangler is seeing packets from port %d as coming from port %d") or 0.
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
// @ref ??_C@_0DP@PFHK@Mangler?5is?5seeing?5packets?5from?5p@=007e6420

unsigned short FirewallSettings::Wait_For_Mangler_Reply(int packet_id, int time)
{
    int index = 0;
    char buffer[456];
    IPXAddressClass address;
    int length;
    unsigned long id;
    unsigned short product_id;
    CDTimerClass<SystemTimerClass> timer(60);
    if (time) {
        timer = CDTimerClass<SystemTimerClass>(time);
    }
    while (timer) {
        unknown_ipx_manager_a40978.Service();
        unknown_481fb0();
        if (index >= unknown_ipx_manager_a40978.Global_Num_Receive()) {
            index = 0;
        }
        ManglerPacket *packet = (ManglerPacket *)buffer;
        if (unknown_ipx_manager_a40978.unknown_525af0(index, buffer, &length, &address, &product_id, &id)
            && product_id == 0xAA03 && packet->Type == 0x2C) {
            int from = packet->Port;
            if (packet_id == (int)id) {
                unsigned short port = packet->SeenPort;
                Debug_Printf("Mangler is seeing packets from port %d as coming from port %d\n", from, port);
                unknown_ipx_manager_a40978.unknown_525b30(index);
                return port;
            }
        }
        index++;
    }
    return 0;
}
