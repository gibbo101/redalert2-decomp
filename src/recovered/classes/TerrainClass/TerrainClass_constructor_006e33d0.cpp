// TerrainClass::TerrainClass(TerrainTypeClass *type, Cell const &cell) (0x006E33D0)
// Takes the type's strength, places the object at the centre of the cell
// (unless it is the zero cell; removed again when placement fails), resets
// the animation timer and registers the object in the terrain list and the
// object index.
#include "shared/terrain.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?unknown_slot60@ObjectClass@@UAEXXZ=005d4e90
// @ref ?Terrains@@3V?$DynamicVectorClass@PAVTerrainClass@@@@A=00a40940
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVObjectClass@@@@A=00abff58
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_7TerrainClass@@6BIPersistStream@@@=007ad3cc
// @ref ??_7TerrainClass@@6BIRTTITypeInfo@@@=007ad3a0
// @ref ??_7TerrainClass@@6BINoticeSink@@@=007ad3c4
// @ref ??_7TerrainClass@@6BINoticeSource@@@=007ad3bc

TerrainClass::TerrainClass(TerrainTypeClass *type, Cell const &cell) :
    Class(type),
    unknown_b4(false),
    unknown_b5(false),
    unknown_b8(0, 0, 0, 0)
{
    AbstractClass::Create_ID();
    Strength = Class->MaxStrength;
    if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        if (!TerrainClass::unknown_slot53(&coord, 0)) {
            ObjectClass::unknown_slot60();
        }
    }
    Animation.Set_Rate(0);
    Terrains.Add(this);
    unknown_object_index_abff58.Add_Index(AbstractClass::Fetch_ID(), this);
}
