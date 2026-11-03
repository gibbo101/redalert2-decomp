// unsigned int CellClass::Preview_Cell_Color(unsigned char &unknown, bool flag) (0x004710D0)
// TibSun Preview_Cell_Color: the cell's two preview pixels, packed first << 16 | second. A visible
// building (unless flag) gives its house colour scheme's colour; under a bridge, the radar colour of
// overlay type 24 (TibSun OVERLAY_BRIDGE1) as a surface pixel; otherwise the preview pixels of the
// cell's tile variation (TibSun Clear_Icon picks it). Cell_Building is unknown_4717b0 and IsUnderBridge
// the accessor unknown_4788d0, both inline in this unit (the original calls Find_Object out of line
// here because of them). The unit's header statics 0x00470490 define CELL_DECLARE_PREVIEW_CELL_COLOR,
// CELL_DECLARE_CLEAR_ICON and RGB_DECLARE_ACCESSORS.
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
#include "shared/overlay_type.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/tileset_index.hpp"
#include "shared/hicolor_pixel.hpp"
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?Clear_Icon@CellClass@@QBEHHH@Z=004767a0
// @ref ?Preview_Tile@IsometricTileTypeClass@@QAEPAGHH@Z=0052e390

unsigned int CellClass::Preview_Cell_Color(unsigned char &unknown, bool flag)
{
    unknown = 0;
    BuildingClass *obj = (BuildingClass *)unknown_4717b0();

    if (!flag && obj != 0 && !obj->Type->Invisible && !obj->Type->InvisibleInGame && obj->unknown_slot25(0, 0) != 5) {
        ColorScheme *scheme = ColorSchemes[obj->House->ColorSchemeIndex];
        unsigned int color = scheme->Converter->Convert(scheme->unknown_0x314);
        return (color << 16) | color;
    }

    if (unknown_4788d0()) {
        RGBClass bridge_color = OverlayTypes[24]->unknown_func_5dd000(0);
        unsigned int color = RGB_To_Pixel(bridge_color.Get_Red(), bridge_color.Get_Green(), bridge_color.Get_Blue());
        return (color << 16) | color;
    }

    IsometricTileTypeClass *ittype;
    int icon;
    if (IsoTileIndex != 0xFFFF) {
        ittype = IsoTileTypes[IsoTileIndex];
    } else {
        ittype = IsoTileTypes[unknown_tileset_a52f00];
    }

    icon = 0;
    if (IsoTileIndex != 0xFFFF) {
        if (ittype->NumTileTypesInSet > 1) {
            if (ittype->Is_Randomized((unsigned char)unknown_11a)) {
                icon = (unknown_140 >> 13) & 1;
            } else {
                int numtiles = ittype->NumTileTypesInSet;
                icon = Clear_Icon(IsoTileIndex, numtiles);
            }
        }
    } else {
        icon = Clear_Icon(unknown_tileset_a52f00, ittype->NumTileTypesInSet);
    }

    IsometricTileTypeClass *next = ittype->Next_Tile_From_Set(icon);
    unsigned short *tile = next->Preview_Tile((unsigned char)unknown_11a, unknown_11b);
    return (tile[0] << 16) | tile[1];
}
