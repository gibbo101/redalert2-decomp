// void TerrainClass::Detach(AbstractClass *target, bool all) (0x006E47A0)
#include "shared/terrain.hpp"
// @ref ?Detach@ObjectClass@@UAEXPAVAbstractClass@@_N@Z=005d3bd0

void TerrainClass::Detach(AbstractClass *target, bool all)
{
    ObjectClass::Detach(target, all);
    if (Class == target) {
        Class = 0;
    }
}
