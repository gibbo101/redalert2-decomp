// void Download_Map_Preview_005c7970() (0x005C7970)
// Gets the host's map preview: acknowledges the preview mode to the host (game mode 3: to
// unknown_address_a3db2c, else to the World Online host by name) until the packet is sent and
// every global send is done, downloads the image file (0x0066AEF0, Get_File_From_Host by its trace), LZO-decompresses
// it (its first word is the decompressed length) and replaces the dialogs' map preview with it.
// The network timing is slower while the download runs.
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/debug_printf.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/lzo_straw.hpp"
#include "shared/map_preview.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_0BI@IOGC@Preview?5mode?5acks?5sent?6?$AA@=007e714c
// @ref ??_C@_0BL@JDDE@Sending?5preview?5mode?5acks?6?$AA@=007e7164
// @ref ??_C@_0BP@HJOD@Starting?5map?5preview?5download?6?$AA@=007e23f0
// @ref ??_C@_0CB@DBLD@Decompressing?5the?5preview?5image?6@=007e2310
// @ref ??_C@_0CC@KPDG@Creating?5the?5new?5preview?5surface@=007e22ec
// @ref ??_C@_0CE@EHOD@got_file?5is?5false?4?5Download?5fail@=007e235c
// @ref ??_C@_0CG@MHNB@Loading?5the?5compressed?5preview?5i@=007e2334
// @ref ??_C@_0DB@NCGA@Cleaning?5up?5the?5temporary?5decomp@=007e22b8
// @ref ??_C@_0DJ@PFBB@Calling?5Get_File_From_Host?5to?5re@=007e2380
// @ref ?Unknown_0061E930@UnknownPreview_0061D430@@QAEXPBG@Z=0061e930
// @ref ?Unknown_0074DA60@@YAPAUUser@WOL@@XZ=0074da60
// @ref ?unknown_address_a3f80c@@3VIPXAddressClass@@A=00a3f80c

void __fastcall Download_Map_Preview_005c7970()
{
    unknown_ipx_manager_a40978.Set_Timing(50, -1, 5000, true);
    Debug_Printf("Starting map preview download\n");
    UnknownGlobalPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x1A;
    Debug_Printf("Sending preview mode acks\n");
    for (;;) {
        int sent;
        if (unknown_game_mode_a3d298 == 3) {
            sent = unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3db2c, 0, 0);
        } else {
            WOL::User *host = Unknown_0074DA60();
            if (host == 0) {
                break;
            }
            sent = unknown_ipx_manager_a40978.unknown_5259a0(&packet, sizeof(packet), 1, Unknown_006FA180(host->name));
        }
        if (sent) {
            break;
        }
        Service_Game_IO_00481fb0();
    }
    while (unknown_ipx_manager_a40978.Global_Num_Send()) {
        Service_Game_IO_00481fb0();
    }
    Debug_Printf("Preview mode acks sent\n");
    unknown_address_a3f80c = unknown_address_a3db2c;
    Debug_Printf("Calling Get_File_From_Host to receive the file download\n");
    char filename[256];
    if (!Unknown_0066aef0(filename, 3, false)) {
        Debug_Printf("got_file is false. Download failed\n");
        unknown_ipx_manager_a40978.Set_Timing(30, -1, 600, true);
        return;
    }
    Debug_Printf("Loading the compressed preview image\n");
    RawFileClass file(filename);
    int size = file.Size();
    char *compressed = (char *)operator new(size);
    file.Read(compressed, size);
    int length = *(int *)compressed;
    Debug_Printf("Decompressing the preview image\n");
    BufferStraw source(compressed + 4, size);
    LZOStraw straw(LZOStraw::DECOMPRESS, 0x2000);
    straw.Get_From(&source);
    unsigned short *image = (unsigned short *)operator new(length * 2);
    straw.Get(image, length);
    Debug_Printf("Creating the new preview surface\n");
    if (unknown_dialog_preview_a72ce8 != 0) {
        delete unknown_dialog_preview_a72ce8;
    }
    unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
    unknown_dialog_preview_a72ce8->Unknown_0061E930(image);
    InvalidateRect(Unknown_00735B10(), 0, FALSE);
    Debug_Printf("Cleaning up the temporary decompression buffers\n");
    operator delete(image);
    operator delete(compressed);
    unknown_ipx_manager_a40978.Set_Timing(30, -1, 600, true);
}
