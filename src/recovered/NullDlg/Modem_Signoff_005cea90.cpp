// void __fastcall Modem_Signoff() (0x005CEA90)
// Unless the 0x02 flag of 0x00A3F600 is set, sends the other side an exit
// event (type 0x13) twice and services the link for 30 ticks (Red Alert's
// Modem_Signoff, which sends EventClass::EXIT the same way).
#include "shared/null_dlg.hpp"
#include "shared/serial_progress.hpp"
#include "shared/event.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/crt_string.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_flags_a3f600@@3EA=00a3f600
// @ref ?Service@NullModemClass@@UAEHXZ=005d0660
// @ref ?Send_Message@NullModemClass@@QAEHPAXHH@Z=005d05f0
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

void __fastcall Modem_Signoff()
{
    EventClass event;

    if (!(unknown_flags_a3f600 & 2)) {
        memset(&event, 0, sizeof(event));
        event.Type = 0x13;
        serial_manager_00a40a28.Send_Message(&event, sizeof(event), 0);
        serial_manager_00a40a28.Send_Message(&event, sizeof(event), 0);
        unsigned long starttime = TickCount.Time();
        while (TickCount.Time() - starttime < 30) {
            serial_manager_00a40a28.Service();
        }
    }
}
