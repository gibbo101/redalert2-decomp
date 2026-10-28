// TerrainTypeClass::TerrainTypeClass(NoInitClass const &noinit) (0x006E53B0)
// Load path: installs the vtables only.
#include "shared/terrain_type.hpp"
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80

TerrainTypeClass::TerrainTypeClass(NoInitClass const &noinit) :
    ObjectTypeClass(noinit),
    RadarColor(noinit)
{
}
