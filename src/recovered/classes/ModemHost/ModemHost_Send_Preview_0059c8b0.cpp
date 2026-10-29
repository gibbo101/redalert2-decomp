// ModemHost::Send_Preview_0059c8b0 (0x0059C8B0)
#include "shared/modem_host.hpp"
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
#include "shared/cd_timer.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/buffer_pipe.hpp"
#include "shared/lzo_pipe.hpp"
#include "shared/session_state.hpp"
// @ref ??_C@_0BK@LFJL@Preview?5size?5is?5?$CFd?5bytes?6?$AA@=007e2754
// @ref ??_C@_0BN@KJJF@Starting?5map?5preview?5upload?6?$AA@=007e2794
// @ref ??_C@_0CC@GEGD@Failed?5to?5get?5SERIAL_PREVIEW_ACK@=007e2770
// @ref ??_C@_0CG@PAND@Compressed?5preview?5image?5is?5?$CFd?5b@=007e272c
// @ref ??_C@_0CO@INCK@Calling?5Send_Remote_File?5to?5send@=007e26f0
// @ref ??_C@_0M@CNHP@Preview?4bin?$AA@=007e2720
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ?Compare_Narrow_00781f20@@YAHPBD0@Z=00781f20
// @ref ?Send_Remote_File_0066bb20@@YI_NPBDH_N1@Z=0066bb20
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Unknown_0061E490@UnknownPreview_0061D430@@QAEPAGHPAH@Z=0061e490
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ??_7BufferPipe@@6B@=0079ea08
void ModemHost::Send_Preview_0059c8b0()
{
    CDTimerClass<SystemTimerClass> timer;
    if (Compare_Narrow_00781f20(unknown_session_a3d298.ScenarioFileName_658, "RandMap.Sed")) {
        return;
    }
    Debug_Printf("Starting map preview upload\n");
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x75;
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
    timer = 600;
    while (serial_manager_00a40a28.Num_Send() > 0 && timer) {
        Service_Game_IO_00481fb0();
    }
    timer = 1800;
    bool acked = false;
    do {
        Service_Game_IO_00481fb0();
        UnknownSerialPacket reply;
        int length;
        if (serial_manager_00a40a28.Get_Message(&reply, &length) > 0 && reply.Command == 0x76) {
            acked = true;
            break;
        }
    } while (timer);
    if (!acked) {
        Debug_Printf("Failed to get SERIAL_PREVIEW_ACK\n");
        return;
    }
    int size = 0;
    unsigned short *image = unknown_dialog_preview_a72ce8->Unknown_0061E490(0x40, &size);
    Debug_Printf("Preview size is %d bytes\n", size);
    char *data = new char[size * 4];
    BufferPipe pipe(data, size * 4);
    LZOPipe lzo(LZOPipe::COMPRESS, 0x2000);
    lzo.Put_To(&pipe);
    int length = lzo.Put(image, size);
    length += lzo.End();
    Debug_Printf("Compressed preview image is %d bytes\n", length);
    RawFileClass file("Preview.bin");
    if (file.Is_Available()) {
        file.Delete();
    }
    file.Open(2);
    file.Write(&size, 4);
    file.Write(data, length);
    file.Close();
    delete data;
    Debug_Printf("Calling Send_Remote_File to send the preview\n");
    Send_Remote_File_0066bb20("Preview.bin", 1, 0, 0);
}
