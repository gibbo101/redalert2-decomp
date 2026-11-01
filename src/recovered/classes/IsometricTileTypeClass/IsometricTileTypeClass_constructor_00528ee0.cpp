// IsometricTileTypeClass::IsometricTileTypeClass(int, int, unsigned char, char const *, bool) (0x00528EE0)
#include "shared/isometric_tile_type.hpp"
#include "shared/object_lists.hpp"
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ??0ObjectTypeClass@@QAE@PBD@Z=005d57f0
// @ref _strncpy=007823d0

IsometricTileTypeClass::IsometricTileTypeClass(int type, int unknown1, unsigned char unknown2, char const *ini_name, bool skip_registration) :
    ObjectTypeClass(ini_name),
    ArrayIndex(type),
    MarbleMadness(0xFFFF),
    NonMarbleMadness(0xFFFF),
    TileSetBaseID(0),
    unknown_274(),
    unknown_28c(0),
    ToSnowTheater(-1),
    ToTemperateTheater(-1),
    unknown_298(-1),
    Offset(Point2D(0, 0)),
    AttachesTo(-1),
    ZAdjust(0),
    Unused1((unsigned char)unknown1),
    unknown_2b0(false),
    IsShadowCaster(false),
    IsAllowToPlace(true),
    IsRequiredForRMG(false),
    unknown_2b4(0),
    unknown_2b8(0),
    Unused2(unknown2),
    NumTileTypesInSet(1),
    unknown_2c4(false),
    unknown_2d5(true),
    unknown_2d6(false),
    UseCount(0)
{
    unknown_objects_ac0cb0.Add(this);
    if (!skip_registration) {
        IsoTileTypes.Add(this);
    }

    Name = FixedString<49>(ini_name);

    Filename[0] = '\0';

    unknown_1ff = true;
    unknown_200 = false;
    unknown_201 = false;
    unknown_202 = true;
    unknown_203 = true;
    unknown_205 = false;
}
