// void CellClass::Unknown_004790F0(int arg1, int intensity, int ambient,
//     int brightness, int tile_brightness, int alt_brightness) (0x004790F0)
#include "shared/cell.hpp"
#include "shared/light_convert.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Clamp_Tile_RGB@@YIXAAH00@Z=005385a0
// @ref ?Find_Or_Make_Drawer@IsometricTileTypeClass@@SIPAVLightConvertClass@@HHH@Z=00529590
// @ref ?Init_Light@CellClass@@QBEXAAH0000000@Z=00479440
// @ref ?unknown_flag_a40958@@3_NA=00a40958


inline void CellClass::Inc_Drawer_Ref_Count(LightConvertClass *drawer) const
{
    drawer->unknown_194++;
}

inline void CellClass::Dec_Drawer_Ref_Count(LightConvertClass *drawer) const
{
    if (unknown_flag_a40958) {
        drawer->unknown_194--;
    }
}

void CellClass::Unknown_004790F0(int arg1, int intensity, int ambient, int brightness, int tile_brightness, int alt_brightness)
{
    bool got_drawer = false;
    int red;
    int green;
    int blue;

    if (arg1 != 0) {
        if (unknown_34 != 0) {
            Dec_Drawer_Ref_Count(unknown_34);
        }
        unknown_34 = (LightConvertClass *)arg1;
        Inc_Drawer_Ref_Count(unknown_34);
        red = unknown_34->Red;
        green = unknown_34->Green;
        blue = unknown_34->Blue;
        got_drawer = true;
    } else if (MapCoords != Cell(0, 0) && MapCoords != Cell(-1, -1)) {
        Init_Light(intensity, ambient, brightness, tile_brightness, alt_brightness, red, green, blue);
        if (unknown_34 != 0) {
            int r = red;
            int g = green;
            int b = blue;
            Clamp_Tile_RGB(r, g, b);
            if (unknown_34->Red != r || unknown_34->Green != g || unknown_34->Blue != b) {
                Dec_Drawer_Ref_Count(unknown_34);
                unknown_34 = 0;
            }
        }
        if (unknown_34 == 0) {
            unknown_34 = IsometricTileTypeClass::Find_Or_Make_Drawer(red, green, blue);
            if (unknown_34 != 0) {
                Inc_Drawer_Ref_Count(unknown_34);
            }
        }
        got_drawer = true;
    }

    if (got_drawer) {
        unknown_104 = intensity;
        unknown_108 = ambient;
        unknown_10a = brightness;
        unknown_10c = tile_brightness;
        unknown_10e = alt_brightness;
        unknown_110 = red;
        unknown_112 = green;
        unknown_114 = blue;
        return;
    }

    unknown_34 = IsometricTileTypeClass::Find_Or_Make_Drawer(1000, 1000, 1000);
    if (unknown_34 != 0) {
        Inc_Drawer_Ref_Count(unknown_34);
    }
    unknown_10a = 1000;
    unknown_10c = 1000;
    unknown_10e = 1000;
    unknown_110 = 1000;
    unknown_112 = 1000;
    unknown_114 = 1000;
    unknown_104 = 0x10000;
    unknown_108 = 0;
}
