// void ScoreClass::Cycle_Wait_Click(bool cycle) (0x00665EE0)
// Waits for a key or click (at least 20 delays), keeping a modem or
// null-modem link alive meanwhile (Westwood's Cycle_Wait_Click; cycle is
// unused).
#include "shared/score.hpp"
#include "shared/keyboard.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
// @ref ?ScoreDelay@ScoreClass@@QAEXH@Z=00667420
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?Check@WWKeyboardClass@@QAE?AW4KeyNumType@@XZ=005322d0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?Response_Time@NullModemClass@@UAEKXZ=005d08e0
// @ref ?Send_Message@NullModemClass@@QAEHPAXHH@Z=005d05f0
// @ref ?Get_Message@NullModemClass@@QAEHPAXPAH@Z=005d0630
// @ref ?Service@NullModemClass@@UAEHXZ=005d0660
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

void ScoreClass::Cycle_Wait_Click(bool cycle)
{
    int minclicks = 20;
    unsigned long timingtime = TickCount.Time();
    UnknownSerialPacket sendpacket;
    UnknownSerialPacket receivepacket;
    int packetlen;

    WWKeyboard->Clear();
    while (minclicks || !WWKeyboard->Check()) {
        if (unknown_game_mode_a3d298 == 2 || unknown_game_mode_a3d298 == 1) {
            if (TickCount.Time() - timingtime > 40) {
                memset(&sendpacket, 0, sizeof(sendpacket));
                sendpacket.Command = 0x6A;
                sendpacket.Timing.ResponseTime = serial_manager_00a40a28.Response_Time();
                sendpacket.ID = (unsigned char)serial_local_player_00a3fb38;
                serial_manager_00a40a28.Send_Message(&sendpacket, sizeof(sendpacket), 0);
                timingtime = TickCount.Time();
            }
            serial_manager_00a40a28.Get_Message(&receivepacket, &packetlen);
            serial_manager_00a40a28.Service();
        }
        ScoreDelay(1);
        if (minclicks) {
            minclicks--;
            WWKeyboard->Clear();
        }
    }
    WWKeyboard->Clear();
}
