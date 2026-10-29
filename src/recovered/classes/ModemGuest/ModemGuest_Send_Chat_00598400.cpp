// ModemGuest::Send_Chat_00598400 (0x00598400)
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
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ?Unknown_005C2DA0@@YIXHPBGPAUHWND__@@@Z=005c2da0
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?Show_Chat_00598510@ModemGuest@@QAEXPBGH0@Z=00598510
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);

void ModemGuest::Send_Chat_00598400(unsigned short const *text)
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
        Show_Chat_00598510(name, unknown_a3d3b4, text);
    }
}
