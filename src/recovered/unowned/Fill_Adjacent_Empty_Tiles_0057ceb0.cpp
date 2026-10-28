// Operation name/free-cdecl spelling are hypotheses; canonical Cell/Map interfaces unchanged.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?unknown_47b7c0@CellClass@@QBE_NXZ=0047b7c0
// @ref ?Adjacent_Cell@CellClass@@QAEAAV1@I@Z=00476ac0
// @ref ?unknown_47b590@CellClass@@QBE_NXZ=0047b590
// @ref ?unknown_tileset_a52c60@@=00a52c60
void Fill_Adjacent_Empty_Tiles_0057ceb0()
{
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        if(cell->unknown_47b7c0()) {
            for(int facing=0;facing<8;facing+=2) {
                CellClass &adjacent=cell->Adjacent_Cell(facing);
                if(adjacent.unknown_47b590())
                    adjacent.IsoTileIndex=unknown_tileset_a52c60;
            }
        }
    }
}
