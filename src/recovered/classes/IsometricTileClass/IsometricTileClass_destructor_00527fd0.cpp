// IsometricTileClass::~IsometricTileClass() (0x00527FD0)
// Leaves the map (slot 52), then the tile list and the object list.
#include "shared/isometric_tile.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?IsoTiles@@3V?$DynamicVectorClass@PAVIsometricTileClass@@@@A=00832448
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ??1ObjectClass@@UAE@XZ=005d2530

IsometricTileClass::~IsometricTileClass()
{
    Unknown_006ECB90(this, true);
    IsometricTileClass::unknown_slot52();
    Type = 0;
    IsoTiles.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
}
