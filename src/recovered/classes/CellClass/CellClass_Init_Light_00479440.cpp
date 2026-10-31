// void CellClass::Init_Light(int &intensity, int &ambient, int &brightness, int &tile_brightness,
//     int &alt_brightness, int &red, int &green, int &blue) const (0x00479440): Westwood's
// Init_Light: the scenario ambient and tints plus every active light within reach of the
// cell's centre, the level light for the cell height (ion storm, dominator or normal), the
// tile tints through Adjust_Tile_RGB, limited to 0..2000; full light for the corner cells.
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/light_source.hpp"
#include "shared/light_convert.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/fast_math.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051FC60@@YA_NXZ=0051fc60
// @ref ?unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z=004706c0
// @ref ?Adjust_Tile_RGB@@YIXAAH0000@Z=005383c0
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?unknown_a40b2c@@3HA=00a40b2c

// Scales a cell's tile brightness and tints by the light intensity (0x005383C0; Westwood's
// Adjust_Tile_RGB, LIGHTCALC).
void __fastcall Adjust_Tile_RGB(int &intensity, int &tile_brightness, int &red, int &green, int &blue);

void CellClass::Init_Light(int &intensity, int &ambient, int &brightness, int &tile_brightness, int &alt_brightness, int &red, int &green, int &blue) const
{
    if (MapCoords != Cell(0, 0) && MapCoords != Cell(-1, -1)) {
        brightness = 1000 * unknown_id_source_a3d290->unknown_22ac / 100;
        red = 1000 * unknown_id_source_a3d290->AmbientRed / 100;
        green = 1000 * unknown_id_source_a3d290->AmbientGreen / 100;
        blue = 1000 * unknown_id_source_a3d290->AmbientBlue / 100;
        ambient = 0;

        for (int i = 0; i < unknown_LightSourceClass_list_00a6e818.Count(); i++) {
            LightSourceClass *light = unknown_LightSourceClass_list_00a6e818[i];
            if (light->Activated && unknown_a40b2c >= light->DetailLevel) {
                CoordStruct cc = unknown_475d60();
                unsigned int dx = cc.X - ((CoordStruct)light->Location).X;
                unsigned int visibility = light->Visibility;
                unsigned int dy = cc.Y - ((CoordStruct)light->Location).Y;
                if (dx * dx + dy * dy <= visibility * visibility) {
                    double fdx = (int)(cc.X - ((CoordStruct)light->Location).X);
                    double fdy = (int)(cc.Y - ((CoordStruct)light->Location).Y);
                    unsigned int dist = (int)Fast_Sqrt(fdx * fdx + fdy * fdy);
                    if (dist <= visibility) {
                        int num = (1000 * visibility - 1000 * dist) / visibility;
                        ambient += (num * light->Intensity) / 1000;
                        red += (num * light->Tint.Red) / 1000;
                        green += (num * light->Tint.Green) / 1000;
                        blue += (num * light->Tint.Blue) / 1000;
                    }
                }
            }
        }

        brightness += ambient;
        alt_brightness = brightness;

        if (Unknown_0051FC50()) {
            brightness += unknown_11b * unknown_id_source_a3d290->IonLevel - unknown_id_source_a3d290->IonGround;
            alt_brightness += (unknown_11b + 4) * unknown_id_source_a3d290->IonLevel - unknown_id_source_a3d290->IonGround;
        } else if (Unknown_0051FC60()) {
            brightness += unknown_11b * unknown_id_source_a3d290->unknown_22f4 - unknown_id_source_a3d290->unknown_22f0;
            alt_brightness += (unknown_11b + 4) * unknown_id_source_a3d290->unknown_22f4 - unknown_id_source_a3d290->unknown_22f0;
        } else {
            brightness += unknown_11b * unknown_id_source_a3d290->AmbientLevel - unknown_id_source_a3d290->AmbientGround;
            alt_brightness += (unknown_11b + 4) * unknown_id_source_a3d290->AmbientLevel - unknown_id_source_a3d290->AmbientGround;
        }

        brightness = (brightness < 2000) ? brightness : 2000;
        tile_brightness = brightness;

        Adjust_Tile_RGB(intensity, tile_brightness, red, green, blue);

        alt_brightness = (alt_brightness * intensity) >> 16;
        alt_brightness = (alt_brightness < 2000) ? alt_brightness : 2000;

        brightness = (brightness > 0) ? brightness : 0;
        tile_brightness = (tile_brightness > 0) ? tile_brightness : 0;
        alt_brightness = (alt_brightness > 0) ? alt_brightness : 0;
    } else {
        intensity = 0x10000;
        ambient = 0;
        brightness = 1000;
        tile_brightness = 1000;
        alt_brightness = 1000;
        red = 1000;
        green = 1000;
        blue = 1000;
    }
}
