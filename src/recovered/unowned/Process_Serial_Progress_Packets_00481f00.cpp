#include "shared/serial_progress.hpp"
// @ref ?Service@NullModemClass@@=005d0660
// @ref ?Get_Message@NullModemClass@@=005d0630
// @ref ?Set_Progress_006201c0@ProgressScreenClass@@=006201c0
// @ref ?serial_manager_00a40a28@@=00a40a28
// @ref ?ProgressScreen@@=00a769e8
// @ref ?serial_session_flags_00a3fac0@@=00a3fac0
// @ref ?serial_local_player_00a3fb38@@=00a3fb38
// @ref ?unknown_game_mode_a3d298@@=00a3d298
// @ref ?unknown_id_source_a3d290@@=00a3d290

void __cdecl Process_Serial_Progress_Packets_00481f00()
{
    unsigned char packet[252];
    int length;
    if (unknown_game_mode_a3d298 == 2 || (serial_session_flags_00a3fac0 & 1)) {
        serial_manager_00a40a28.Service();
        if (unknown_id_source_a3d290->unknown_22fc) {
            while (serial_manager_00a40a28.Get_Message(packet, &length) > 0) {
                // Preserve the original DWORD sender read and overlapping unaligned
                // signed progress read. Complete packet format remains unknown.
                if (*(int *)packet == 108 &&
                    (*(unsigned int *)(packet + 24) & 255) != serial_local_player_00a3fb38) {
                    ProgressScreen.Set_Progress_006201c0(
                        1, (double)*(int *)(packet + 25), Point2D(-1, -1));
                }
            }
        }
    }
}
