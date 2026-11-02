// bool TerrainTypeClass::Read_INI(CCINIClass &ini) (0x006E5630)
// Reads the terrain keys; the foundation comes from the art INI (image
// section) and selects the occupation list; the radar colour is the first
// image frame's colour. Veinholes clear unknown_204 and set unknown_201.
// A strength of -1 takes the rules default (+0xE1C).
#include "shared/terrain_type.hpp"
// @ref ??_C@_0L@BABL@IsVeinhole?$AA@=007f8254
// @ref ??_C@_0L@CDEF@WaterBound?$AA@=007d112c
// @ref ??_C@_0P@FLHG@SpawnsTiberium?$AA@=007f8244
// @ref ??_C@_0M@BBJO@IsFlammable?$AA@=007f8238
// @ref ??_C@_0L@LNJG@Foundation?$AA@=007d0b7c
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_0L@MMAI@IsAnimated?$AA@=007f822c
// @ref ??_C@_0O@OPKC@AnimationRate?$AA@=007f821c
// @ref ??_C@_0BF@KIHN@AnimationProbability?$AA@=007f8204
// @ref ??_C@_0BI@MKJG@TemperateOccupationBits?$AA@=007f81ec
// @ref ??_C@_0BD@GEGK@SnowOccupationBits?$AA@=007f81d8
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/shape_file.hpp"
#include "shared/rules.hpp"
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ?Get_Foundation@CCINIClass@@QBEHPBD0H@Z=0046a260
// @ref ?unknown_foundation_lists_ac0430@@3PAY09VCell@@A=00ac0430
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0

// The colour stored in a shape frame header (+0x0C; hypothesis: the radar
// colour of the frame).
static inline RGBClass Frame_Color(ShapeFileStruct const *shape, int frame)
{
    ShapeFileFrameStruct const *header = shape->Get_Frame(frame);
    if (header != 0) {
        unsigned char const *color = (unsigned char const *)&header->unknown_0C;
        return RGBClass(color[0], color[1], color[2]);
    }
    return RGBClass();
}

bool TerrainTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        if (MaxStrength == -1) {
            MaxStrength = Rules->unknown_e1c;
        }
        char const *section = ID;
        IsVeinhole = ini.Get_Bool(section, "IsVeinhole", IsVeinhole);
        if (IsVeinhole) {
            unknown_204 = false;
            unknown_201 = true;
        }
        WaterBound = ini.Get_Bool(section, "WaterBound", WaterBound);
        SpawnsTiberium = ini.Get_Bool(section, "SpawnsTiberium", SpawnsTiberium);
        IsFlammable = ini.Get_Bool(section, "IsFlammable", IsFlammable);
        Foundation = ArtINI.Get_Foundation(unknown_1c8, "Foundation", Foundation);
        OccupyList = unknown_foundation_lists_ac0430[Foundation];
        if (!unknown_1fc) {
            char fullname[512];
            _makepath(fullname, 0, 0, unknown_1c8, ".SHP");
            unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
        }
        ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_slot39();
        if (shape != 0) {
            RadarColor = Frame_Color(shape, 0);
        }
        IsAnimated = ini.Get_Bool(section, "IsAnimated", IsAnimated);
        AnimationRate = ini.Get_Int(section, "AnimationRate", AnimationRate);
        AnimationProbability = ini.Get_Double(section, "AnimationProbability", AnimationProbability);
        TemperateOccupationBits = ini.Get_Int(section, "TemperateOccupationBits", TemperateOccupationBits);
        SnowOccupationBits = ini.Get_Int(section, "SnowOccupationBits", SnowOccupationBits);
        return true;
    }
    return false;
}
