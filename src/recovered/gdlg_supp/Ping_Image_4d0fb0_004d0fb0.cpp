// Surface *__fastcall Ping_Image_4d0fb0(int ping) (0x004D0FB0)
// The ping image of a connection quality (0 "pingg.pcx", 1 "pingy.pcx",
// 2 "pingr.pcx"); null for any other value.
#include "shared/gdlg_supp.hpp"
#include "shared/pcx_cache.hpp"
// @ref ?unknown_bitmap_writer_a76378@@3VUnknownBitmapWriter@@A=00a76378
// @ref ?Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z=0068ca40
// @ref ?unknown_ping_images_7f86dc@@3PAPBDA=007f86dc

Surface *__fastcall Ping_Image_4d0fb0(int ping)
{
    Surface *image = 0;
    if (ping == 0) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_ping_images_7f86dc[0], 0);
    } else if (ping == 1) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_ping_images_7f86dc[1], 0);
    } else if (ping == 2) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_ping_images_7f86dc[2], 0);
    }
    return image;
}
