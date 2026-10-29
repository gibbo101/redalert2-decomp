// ModemGuest::Receive_Preview_005989b0 (0x005989B0)
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
#include "shared/cd_timer.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/lzo_straw.hpp"
// @ref ??_C@_0BH@HIIN@Preview?5mode?5ack?5sent?6?$AA@=007e23bc
// @ref ??_C@_0BK@CAE@Sending?5preview?5mode?5ack?6?$AA@=007e23d4
// @ref ??_C@_0BP@HJOD@Starting?5map?5preview?5download?6?$AA@=007e23f0
// @ref ??_C@_0CB@DBLD@Decompressing?5the?5preview?5image?6@=007e2310
// @ref ??_C@_0CC@KPDG@Creating?5the?5new?5preview?5surface@=007e22ec
// @ref ??_C@_0CE@EHOD@got_file?5is?5false?4?5Download?5fail@=007e235c
// @ref ??_C@_0CG@MHNB@Loading?5the?5compressed?5preview?5i@=007e2334
// @ref ??_C@_0DB@NCGA@Cleaning?5up?5the?5temporary?5decomp@=007e22b8
// @ref ??_C@_0DJ@PFBB@Calling?5Get_File_From_Host?5to?5re@=007e2380
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Unknown_0061E930@UnknownPreview_0061D430@@QAEXPBG@Z=0061e930
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?Unknown_0066aef0@@YI_NPADH_N@Z=0066aef0

void ModemGuest::Receive_Preview_005989b0()
{
    CDTimerClass<SystemTimerClass> timer;
    Debug_Printf("Starting map preview download\n");
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x76;
    Debug_Printf("Sending preview mode ack\n");
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
    timer = 600;
    while (serial_manager_00a40a28.Num_Send() > 0 && timer) {
        Service_Game_IO_00481fb0();
    }
    Debug_Printf("Preview mode ack sent\n");
    Debug_Printf("Calling Get_File_From_Host to receive the file download\n");
    char filename[256];
    if (!Unknown_0066aef0(filename, 1, false)) {
        Debug_Printf("got_file is false. Download failed\n");
        return;
    }
    Debug_Printf("Loading the compressed preview image\n");
    RawFileClass file(filename);
    int size = file.Size();
    char *data = new char[size];
    file.Read(data, size);
    int length = *(int *)data;
    Debug_Printf("Decompressing the preview image\n");
    BufferStraw straw(data + 4, size);
    LZOStraw lzo(LZOStraw::DECOMPRESS, 0x2000);
    lzo.Get_From(&straw);
    unsigned short *image = new unsigned short[length];
    lzo.Get(image, length);
    Debug_Printf("Creating the new preview surface\n");
    if (unknown_dialog_preview_a72ce8) {
        delete unknown_dialog_preview_a72ce8;
    }
    unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
    unknown_dialog_preview_a72ce8->Unknown_0061E930(image);
    InvalidateRect(Window, 0, 0);
    Debug_Printf("Cleaning up the temporary decompression buffers\n");
    delete image;
    delete data;
}
