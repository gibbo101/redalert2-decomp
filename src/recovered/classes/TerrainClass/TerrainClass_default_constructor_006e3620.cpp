// TerrainClass::TerrainClass() (0x006E3620)
// An untyped terrain object, registered in the terrain list and the object
// index.
#include "shared/terrain.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0

TerrainClass::TerrainClass() :
    Class(0),
    unknown_b4(false),
    unknown_b5(false),
    unknown_b8(0, 0, 0, 0)
{
    Terrains.Add(this);
    unknown_object_index_abff58.Add_Index(AbstractClass::Fetch_ID(), this);
}
