// void IsometricTileTypeClass::unknown_func_52e3d0() (0x0052E3D0): rebuilds the preview colour
// tables, 13 light levels of the low and high colour per sub tile (TibSun Build_Preview_Tiles).
#include "shared/isometric_tile_type.hpp"
#include "shared/hicolor.hpp"
// @ref ??0RGBClass@@QAE@ABV0@0M@Z=0063cc80
// @ref ?Set@RGBClass@@QAEAAV1@ABV1@M@Z=0063cdf0

void IsometricTileTypeClass::unknown_func_52e3d0()
{
    int i;
    int j;
    IsoTileImageStruct *tileset = (IsoTileImageStruct *)unknown_a4;
    for (i = 0; i < unknown_274.Count(); i++) {
        if (unknown_274[i] != 0) {
            delete [] unknown_274[i];
        }
    }
    unknown_274.Clear();

    for (i = 0; i < tileset->unknown_00[0] * tileset->unknown_00[1]; i++) {
        if (tileset->Tiles[i] != 0) {
            unsigned short *buffer = new unsigned short[24 + 2];
            IsoTileCellStruct const *record = (IsoTileCellStruct const *)tileset->Tiles[i];
            unknown_274.Add(buffer);
            RGBClass low(record->LowRed, record->LowGreen, record->LowBlue);
            RGBClass high(record->HighRed, record->HighGreen, record->HighBlue);
            static float const _brightness_factor = 1.4f;
            RGBClass alow((NoInitClass()));
            alow.Set(low, _brightness_factor);
            RGBClass ahigh((NoInitClass()));
            ahigh.Set(high, _brightness_factor);
            unsigned short *ptr = buffer;
            RGBClass tmp((NoInitClass()));
            for (j = 0; j <= 12; j++) {
                tmp = RGBClass(low, alow, float((double)j / 12.0f));
                ptr[0] = (unsigned short)Build_Hicolor_Pixel(tmp.Red, tmp.Green, tmp.Blue);
                tmp = RGBClass(high, ahigh, float((double)j / 12.0f));
                ptr[1] = (unsigned short)Build_Hicolor_Pixel(tmp.Red, tmp.Green, tmp.Blue);
                ptr += 2;
            }
        } else {
            unknown_274.Add(0);
        }
    }
}
// @ref _?_brightness_factor@?M@??unknown_func_52e3d0@IsometricTileTypeClass@@QAEXXZ@4MB=007a5134
// @ref __real@8@3ffbaaaaaaaaaaaaa800=007a5288
