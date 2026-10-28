// TerrainClass::~TerrainClass() (0x006E3000)
// Leaves the notice lists, the terrain list and the object index; when the
// 0x00A40958 flag is set a typed object first leaves the map (slot 52).
#include "shared/terrain.hpp"
#include "shared/terrain_object_index.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVObjectClass@@_N@Z=006ecb90
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVObjectClass@@@@A=00abff58
// @ref _qsort=00781d46
// @ref ??1ObjectClass@@UAE@XZ=005d2530

TerrainClass::~TerrainClass()
{
    Unknown_006ECB90(this, true);
    Terrains.Delete(this);
    if (unknown_flag_a40958 && Class != 0) {
        unknown_7d = true;
        TerrainClass::unknown_slot52();
    }
    unknown_object_index_abff58.Remove_Index(AbstractClass::Fetch_ID());
}
