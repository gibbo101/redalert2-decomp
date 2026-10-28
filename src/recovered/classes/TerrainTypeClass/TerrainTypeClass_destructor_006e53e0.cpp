// TerrainTypeClass::~TerrainTypeClass() (0x006E53E0)
// Leaves the notice lists and TerrainTypes.
#include "shared/terrain_type.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60

TerrainTypeClass::~TerrainTypeClass()
{
    Unknown_006ECB90((ObjectClass *)(AbstractClass *)this, true);
    TerrainTypes.Delete(this);
}
