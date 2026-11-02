// ModemGuest::Send_Options_00598330 (0x00598330)
#include "shared/modem_guest.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?version_object_00a40c88@@3VVersionClass@@A=00a40c88
// @ref ?Unknown_007131b0@VersionClass@@QAEKXZ=007131b0
// @ref ?Unknown_007131c0@VersionClass@@QAEKXZ=007131c0
// @ref ?Unknown_00737af0@@YAHXZ=00737af0
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Send_Options_00598330()
{
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x65;
    *(int *)&packet.unknown_19[0x86 - 0x19] = unknown_50;
    *(int *)&packet.unknown_19[0xD4 - 0x19] = unknown_54;
    *(int *)&packet.unknown_19[0xD0 - 0x19] = unknown_58;
    *(unsigned long *)&packet.unknown_19[0xD8 - 0x19] = Unknown_00737af0();
    *(unsigned long *)&packet.unknown_19[0x1E - 0x19] = version_object_00a40c88.Unknown_007131b0();
    *(unsigned long *)&packet.unknown_19[0x22 - 0x19] = version_object_00a40c88.Unknown_007131c0();
    packet.ID = serial_local_player_00a3fb38;
    strcpy(packet.Name, unknown_name_a3d3a0);
    *(int *)&packet.unknown_19[0] = unknown_a3d3bc;
    packet.unknown_19[0x1D - 0x19] = unknown_a3d3b4;
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
}
