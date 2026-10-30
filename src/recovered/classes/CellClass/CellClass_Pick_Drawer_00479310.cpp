// void CellClass::Pick_Drawer(LightConvertClass *&drawer, int &intensity, int &ambient,
//     int &brightness, int &tile_brightness, int &alt_brightness) const (0x00479310)
#include "shared/cell.hpp"
#include "shared/light_convert.hpp"
#include "shared/map_cell_view.hpp"
// @ref ?Clamp_Tile_RGB@@YIXAAH00@Z=005385a0
// @ref ?Find_Or_Make_Drawer@IsometricTileTypeClass@@SIPAVLightConvertClass@@HHH@Z=00529590
// @ref ?Init_Light@CellClass@@QBEXAAH0000000@Z=00479440


void CellClass::Pick_Drawer(LightConvertClass *&drawer, int &intensity, int &ambient, int &brightness, int &tile_brightness, int &alt_brightness) const
{
    intensity = 0x10000;
    ambient = 0;
    brightness = 1000;
    tile_brightness = 1000;
    alt_brightness = 1000;

    int red;
    int green;
    int blue;

    if (MapCoords != Cell(0, 0) && MapCoords != Cell(-1, -1)) {
        Init_Light(intensity, ambient, brightness, tile_brightness, alt_brightness, red, green, blue);

        bool new_drawer = false;
        if (unknown_34 != 0) {
            int r = red;
            int g = green;
            int b = blue;
            Clamp_Tile_RGB(r, g, b);
            if (unknown_34->Red == r && unknown_34->Green == g && unknown_34->Blue == b) {
                drawer = unknown_34;
            } else {
                new_drawer = true;
            }
        } else {
            new_drawer = true;
        }
        if (new_drawer) {
            drawer = IsometricTileTypeClass::Find_Or_Make_Drawer(red, green, blue);
        }
    } else {
        drawer = IsometricTileTypeClass::Find_Or_Make_Drawer(1000, 1000, 1000);
    }
}
