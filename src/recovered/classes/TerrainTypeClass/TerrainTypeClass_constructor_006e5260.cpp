// TerrainTypeClass::TerrainTypeClass(char const *ini_name) (0x006E5260)
// Default terrain values, registration in TerrainTypes, then the default
// strength (-1: the rules value, see Read_INI) and armor (6; hypothesis).
#include "shared/terrain_type.hpp"
// @ref ??0ObjectTypeClass@@QAE@PBD@Z=005d57f0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?TerrainTypes@@3V?$DynamicVectorClass@PAVTerrainTypeClass@@@@A=00a40320
// @ref ??_7TerrainTypeClass@@6BIPersistStream@@@=007ad5e0
// @ref ??_7TerrainTypeClass@@6BIRTTITypeInfo@@@=007ad5c4
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?unknown_slot39@ObjectTypeClass@@UBEPAXXZ=0041c300
// @ref ??_7TerrainTypeClass@@6BINoticeSink@@@=007ad5bc
// @ref ??_7TerrainTypeClass@@6BINoticeSource@@@=007ad5b4

TerrainTypeClass::TerrainTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name),
    ArrayIndex(-1),
    Foundation(0),
    TemperateOccupationBits(7),
    SnowOccupationBits(7),
    AnimationRate(0),
    AnimationProbability(0),
    WaterBound(false),
    SpawnsTiberium(false),
    IsFlammable(false),
    IsAnimated(false),
    IsVeinhole(false),
    OccupyList(0)
{
    AbstractClass::Create_ID();
    unknown_200 = false;
    unknown_204 = true;
    unknown_1ff = true;
    unknown_201 = false;
    unknown_202 = true;
    TerrainTypes.Add(this);
    ArrayIndex = TerrainTypes.ID(this);
    MaxStrength = -1;
    unknown_9c = 6;
}
