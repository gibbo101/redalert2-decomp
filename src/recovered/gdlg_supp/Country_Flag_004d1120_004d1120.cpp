// Surface *__fastcall Country_Flag_004d1120(int country) (0x004D1120)
// A country's flag image: countries 0-8 "usai.pcx" ... "rusi.pcx", -2
// "rani.pcx" (random), -3 "obsi.pcx" (observer); null for any other value.
#include "shared/progress_screen.hpp"
#include "shared/pcx_cache.hpp"
// @ref ?unknown_bitmap_writer_a76378@@3VUnknownBitmapWriter@@A=00a76378
// @ref ?Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z=0068ca40
// @ref ?unknown_flag_images_7f86b0@@3PAPBDA=007f86b0

Surface *__fastcall Country_Flag_004d1120(int country)
{
    Surface *image = 0;
    if (country == -2) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[0], 0);
    } else if (country == 0) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[2], 0);
    } else if (country == 1) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[3], 0);
    } else if (country == 2) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[4], 0);
    } else if (country == 3) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[5], 0);
    } else if (country == 4) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[6], 0);
    } else if (country == 5) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[7], 0);
    } else if (country == 6) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[8], 0);
    } else if (country == 7) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[9], 0);
    } else if (country == 8) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[10], 0);
    } else if (country == -3) {
        image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_flag_images_7f86b0[1], 0);
    }
    return image;
}
