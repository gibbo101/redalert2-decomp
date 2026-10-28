// bool TerrainTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x006E5560)
// Creates a terrain object of this type at the cell.
#include "shared/terrain_type.hpp"
#include "shared/terrain.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0TerrainClass@@QAE@PAVTerrainTypeClass@@ABVCell@@@Z=006e33d0

bool TerrainTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    if (new TerrainClass((TerrainTypeClass *)this, cell) != 0) {
        return true;
    }
    return false;
}
