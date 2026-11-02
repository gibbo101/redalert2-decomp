// ModemHost::Send_Chat_0059bfa0 (0x0059BFA0)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/lobby.hpp"
#include "shared/comm_buffer.hpp"
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref __imp__GetDlgItem@8=0079a49c
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);


void ModemHost::Send_Chat_0059bfa0(unsigned short const *text)
{
    if (text) {
        UnknownSerialPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 0x68;
        strcpy(packet.Name, unknown_name_a3d3a0);
        packet.ID = unknown_a3d3b4;
        wcscpy(packet.Message, text);
        serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
        serial_manager_00a40a28.Service();
        unsigned short *name = Unknown_006FA180(unknown_name_a3d3a0);
        Show_Chat_0059c0b0(name, unknown_a3d3b4, text);
    }
}
