// bool ObjectTypeClass::Read_INI(CCINIClass &ini) (0x005D7810)
// The abstract type's keys, then the object keys from the rules section and
// the art keys from the image's art INI section; non-voxel types load their
// theater image, and an AlphaImage= is looked up in the mixfiles.
// Members by INI key: unknown_1c8 Image, unknown_1e3 AlphaImage,
// unknown_1c0 CrushSound, unknown_1c4 AmbientSound, unknown_1fd Crushable,
// unknown_1fe Bombable, unknown_1b8 NoSpawnAlt, unknown_1e1
// AlternateArcticArt, unknown_1ff RadarInvisible, unknown_200 Selectable,
// unknown_201 LegalTarget, unknown_9c Armor, MaxStrength Strength,
// unknown_203 Immune, unknown_202 Insignificant, unknown_208
// HasRadialIndicator, unknown_209 IgnoresFirestorm;
// art: unknown_20a UseLineTrail, unknown_210
// LineTrailColorDecrement, unknown_1fc Theater, unknown_207 NewTheater,
// unknown_206 Voxel.
#include "shared/object_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/rgb_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/anim_type.hpp"
// @ref ?Read_INI@AbstractTypeClass@@UAE_NAAVCCINIClass@@@Z=004107e0
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ?Get_Bool@INIClass@@QBE_NPBD0_N@Z=0050f410
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ?Get_ArmorType@CCINIClass@@QBE?AW4ArmorType@@PBD0W42@@Z=0046a8b0
// @ref ?Get_RGB@CCINIClass@@QBE?AVRGBClass@@PBD0ABV2@@Z=0046a010
// @ref ?From_Name@VocClass@@SIHPBD@Z=00714940
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref __makepath=007831f0
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_0BB@LLC@IgnoresFirestorm?$AA@=007e8154
// @ref ??_C@_0BD@COFP@HasRadialIndicator?$AA@=007e8174
// @ref ??_C@_0BD@GPAN@AlternateArcticArt?$AA@=007e81d4
// @ref ??_C@_0BI@IOOA@LineTrailColorDecrement?$AA@=007e811c
// @ref ??_C@_0L@CNEJ@NewTheater?$AA@=007ceff8
// @ref ??_C@_0L@DCMG@Selectable?$AA@=007e81b8
// @ref ??_C@_0L@HJPN@NoSpawnAlt?$AA@=007e81e8
// @ref ??_C@_0L@LKAI@CrushSound?$AA@=007e821c
// @ref ??_C@_05LADG@Image?$AA@=007cfddc
// @ref ??_C@_0L@MJEL@AlphaImage?$AA@=007e8228
// @ref ??_C@_0M@BINO@LegalTarget?$AA@=007e81ac
// @ref ??_C@_0M@IKAG@RadialColor?$AA@=007e8168
// @ref ??_C@_0N@GGEJ@AmbientSound?$AA@=007e820c
// @ref ??_C@_0N@PMCL@UseLineTrail?$AA@=007e8144
// @ref ??_C@_0O@NPAM@Insignificant?$AA@=007e8188
// @ref ??_C@_0P@DBGJ@LineTrailColor?$AA@=007e8134
// @ref ??_C@_0P@MPCB@RadarInvisible?$AA@=007e81c4
// @ref ??_C@_05KFDN@Armor?$AA@=007d3824
// @ref ??_C@_05KJKE@Voxel?$AA@=007e8114
// @ref ??_C@_06KOGP@Immune?$AA@=007e8198
// @ref ??_C@_07OHHF@Theater?$AA@=007cf004
// @ref ??_C@_08GLCH@Strength?$AA@=007e81a0
// @ref ??_C@_08HBNM@Bombable?$AA@=007e81f4
// @ref ??_C@_09CJEL@Crushable?$AA@=007e8200

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

bool ObjectTypeClass::Read_INI(CCINIClass &ini)
{
    if (AbstractTypeClass::Read_INI(ini)) {
        char buffer[25];
        strcpy(buffer, unknown_1c8);
        ini.Get_String(ID, "Image", buffer, unknown_1c8.Buffer, sizeof(unknown_1c8.Buffer));
        strcpy(buffer, unknown_1e3);
        ini.Get_String(ID, "AlphaImage", buffer, unknown_1e3.Buffer, sizeof(unknown_1e3.Buffer));

        char name[128];
        int sound = unknown_1c0;
        if (ini.Get_String(ID, "CrushSound", unknown_string_83c55c, name, sizeof(name))) {
            int found = VocClass::From_Name(name);
            if (found != -1) {
                sound = found;
            }
        }
        unknown_1c0 = sound;
        sound = unknown_1c4;
        int found;
        if (!ini.Get_String(ID, "AmbientSound", unknown_string_83c55c, name, sizeof(name)) || (found = VocClass::From_Name(name)) == -1) {
            found = sound;
        }
        unknown_1c4 = found;

        unknown_1fd = ini.Get_Bool(ID, "Crushable", unknown_1fd);
        unknown_1fe = ini.Get_Bool(ID, "Bombable", unknown_1fe);
        unknown_1b8 = ini.Get_Bool(ID, "NoSpawnAlt", unknown_1b8);
        unknown_1e1 = ini.Get_Bool(ID, "AlternateArcticArt", unknown_1e1);
        unknown_1ff = ini.Get_Bool(ID, "RadarInvisible", unknown_1ff);
        unknown_200 = ini.Get_Bool(ID, "Selectable", unknown_200);
        unknown_201 = ini.Get_Bool(ID, "LegalTarget", unknown_201);
        unknown_9c = ini.Get_ArmorType(ID, "Armor", (ArmorType)unknown_9c);
        MaxStrength = ini.Get_Int(ID, "Strength", MaxStrength);
        unknown_203 = ini.Get_Bool(ID, "Immune", unknown_203);
        unknown_202 = ini.Get_Bool(ID, "Insignificant", unknown_202);
        unknown_208 = ini.Get_Bool(ID, "HasRadialIndicator", unknown_208);
        RadialColor = ini.Get_RGB(ID, "RadialColor", RadialColor);
        unknown_209 = ini.Get_Bool(ID, "IgnoresFirestorm", unknown_209);

        unknown_20a = ArtINI.Get_Bool(unknown_1c8, "UseLineTrail", unknown_20a);
        LineTrailColor = ArtINI.Get_RGB(unknown_1c8, "LineTrailColor", LineTrailColor);
        unknown_210 = ArtINI.Get_Int(unknown_1c8, "LineTrailColorDecrement", unknown_210);
        unknown_1fc = ArtINI.Get_Bool(unknown_1c8, "Theater", unknown_1fc);
        unknown_207 = ArtINI.Get_Bool(unknown_1c8, "NewTheater", unknown_207);
        unknown_206 = ArtINI.Get_Bool(unknown_1c8, "Voxel", unknown_206);
        if (!unknown_206) {
            unknown_func_5d7630();
        }

        if (unknown_1e3[0] != 0) {
            char filename[260];
            _makepath(filename, 0, 0, unknown_1e3, ".SHP");
            unknown_ac = (int)MixFileClass::Retrieve(filename);
        }
        return true;
    }
    return false;
}
