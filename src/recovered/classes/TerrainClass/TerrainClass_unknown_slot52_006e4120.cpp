// bool TerrainClass::unknown_slot52() (0x006E4120)
// Takes the terrain object off the map (ObjectClass slot 52). Unless it was
// never placed (+0x76) every neighbouring cell counts one adjacent terrain
// object less and the cell under it loses the Monolith occupation bit; the
// cell's overlay is then cleared and, outside the map editor mode,
// the cell is refreshed (map, radar). Returns the base result.
#include "shared/terrain.hpp"
// @ref ?unknown_slot52@ObjectClass@@UAE_NXZ=005d3700
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Unknown_00472540@CellClass@@QAEXH@Z=00472540

bool TerrainClass::unknown_slot52()
{
    if (!unknown_76) {
        Cell cell = unknown_slot104();
        for (int facing = 0; facing < 8; facing++) {
            CellClass &next = Map[Adjacent_Cell(cell, facing)];
            next.unknown_122--;
        }
        CoordStruct coord = Coord;
        ((TerrainCellView &)Map[coord]).unknown_124.Occupy.Monolith = false;
    }
    Cell cell = unknown_slot104();
    bool result = ObjectClass::unknown_slot52();
    Map[cell].Unknown_00472540(-1);
    if (unknown_a40774 == 0) {
        Map.Unknown_0054FB20(cell);
        Map.Unknown_00566340(cell);
        ((RadarClass &)Map).Unknown_00631570(cell);
    }
    return result;
}
