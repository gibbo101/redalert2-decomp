// ObjectClass *TerrainTypeClass::unknown_slot35(HouseClass *house) const (0x006E55A0)
// Creates an unplaced terrain object of this type (at the zero cell).
#include "shared/terrain_type.hpp"
#include "shared/terrain.hpp"
// @ref ??0TerrainClass@@QAE@PAVTerrainTypeClass@@ABVCell@@@Z=006e33d0

ObjectClass *TerrainTypeClass::unknown_slot35(HouseClass *house) const
{
    return new TerrainClass((TerrainTypeClass *)this, unknown_geometry_k);
}
