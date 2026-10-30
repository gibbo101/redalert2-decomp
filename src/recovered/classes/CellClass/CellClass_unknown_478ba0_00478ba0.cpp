// bool CellClass::unknown_478ba0(bool arg1) (0x00478BA0)
// Westwood's CellClass::Can_Tiberium_Germinate (arg1 unused; the spread
// 0x00478A40 really passes a TiberiumClass *, other callers 0): the map accepts the cell
// (Map.Unknown_0055A660), it is not flagged 0x500, holds no living visible
// building and no tiberium-spawning terrain object, its land allows building,
// it has no overlay, +0x11C is clear and its tile type allows it (+0x2D6; any
// tile outside the type list does).
#include "shared/cell.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/terrain.hpp"
#include "shared/terrain_type.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

bool CellClass::unknown_478ba0(bool arg1)
{
    if (Map.Unknown_0055A660(MapCoords, true) && (unknown_140 & 0x500) == 0) {
        BuildingClass *building = (BuildingClass *)unknown_4717b0();
        if (building != 0 && building->Strength > 0 && !building->Type->Invisible && !building->Type->InvisibleInGame) {
            return false;
        }
        TerrainClass *terrain = (TerrainClass *)Cell_Terrain();
        if (terrain != 0 && terrain->Class->SpawnsTiberium) {
            return false;
        }
        if (Ground[unknown_ec].Build && OverlayIndex == -1 && !unknown_11c
            && (IsoTileIndex < 0 || IsoTileIndex >= IsoTileTypes.Count() || IsoTileTypes[IsoTileIndex]->unknown_2d6)) {
            return true;
        }
    }
    return false;
}
