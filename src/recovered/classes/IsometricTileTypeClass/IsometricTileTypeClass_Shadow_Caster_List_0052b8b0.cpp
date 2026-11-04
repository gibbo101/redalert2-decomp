// Cell const *IsometricTileTypeClass::Shadow_Caster_List() const (0x0052B8B0)
// The cells a cliff tile's shadow darkens, relative to the tile, for each of
// the 40 tiles of a shadow casting cliff set (ShadowCasterTiles), ending in
// the 0x7FFF end marker; 0 for a tile that casts no shadow (TibSun
// Shadow_Caster_List; the cells redraw with the cliff).
#include "shared/isometric_tile_type.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _?$S70@?4??Shadow_Caster_List@IsometricTileTypeClass@@QBEPBVCell@@XZ@4EA=00a6e100
// @ref _?_list@?4??Shadow_Caster_List@IsometricTileTypeClass@@QBEPBVCell@@XZ@4QAY05$$CBUUnknownStaticCell@@A=00a6cb80
// @ref _$E71=0052c220
// @ref _atexit=0078298a

Cell const *IsometricTileTypeClass::Shadow_Caster_List() const
{
    if (IsShadowCaster) {
        static UnknownStaticCell const _list[40][6] = {
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -1), Cell(0, -1), Cell(-1, -2), unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -1), Cell(0, -1), Cell(-1, -2), unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(-1, -3), Cell(0, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(-1, -3), Cell(0, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(-1, -3), Cell(0, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -3), Cell(1, -3), Cell(-1, -3), Cell(-2, -3), unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -3), Cell(-1, -3), Cell(-2, -3), Cell(-3, -2), unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -3), Cell(-1, -3), Cell(-2, -3), unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -3), Cell(-1, -3), Cell(-2, -3), unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(-2, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(-2, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { Cell(0, -3), unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
            { unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, unknown_geometry_k, Cell(0x7FFF, 0x7FFF) },
        };

        for (int i = 0; i < 5; i++) {
            int index = ArrayIndex - ShadowCasterTiles[i];
            if (index >= 0 && index < 40) {
                return &_list[index][0].Cell;
            }
        }
    }
    return 0;
}
