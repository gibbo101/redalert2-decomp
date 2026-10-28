// bool OverlayTypeClass::Read_INI(CCINIClass &ini) (0x005DCAA0)
// Reads the overlay keys; "DamageLevels" and "DemandLoad" come from the art
// INI (image section). Tiberium is armor 6 (hypothesis) and defaults to
// land type 5. Images that are not theater-specific or demand-loaded are
// loaded at once.
#include "shared/overlay_type.hpp"
// @ref ??_C@_08GLCH@Strength?$AA@=007e81a0
// @ref ??_C@_04PHLO@Wall?$AA@=007d0fa8
// @ref ??_C@_08EAIC@Tiberium?$AA@=007cdcd0
// @ref ??_C@_08LAIG@Explodes?$AA@=007e8c20
// @ref ??_C@_0L@BGFD@DemandLoad?$AA@=007ceeac
// @ref ??_C@_07FLNF@IsVeins?$AA@=007cee50
// @ref ??_C@_04JOBE@Land?$AA@=007e8c44
// @ref ??_C@_05CFAP@Crate?$AA@=007e8c3c
// @ref ??_C@_07NEEM@IsARock?$AA@=007e8bac
// @ref ??_C@_08CODE@CellAnim?$AA@=007e8c08
// @ref ??_C@_08GJEE@IsRubble?$AA@=007e8ba0
// @ref ??_C@_08MHOG@DrawFlat?$AA@=007e8bb4
// @ref ??_C@_09BOEE@Overrides?$AA@=007e8c14
// @ref ??_C@_0BC@HDE@NoUseTileLandType?$AA@=007e8be4
// @ref ??_C@_0BC@KKKL@IsVeinholeMonster?$AA@=007e8bd0
// @ref ??_C@_0N@DJHE@DamageLevels?$AA@=007e8bf8
// @ref ??_C@_0N@OGBF@CrateTrigger?$AA@=007e8c2c
// @ref ??_C@_0O@DHEF@ChainReaction?$AA@=007e8bc0
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?Find_Or_Make@AnimTypeClass@@SIPAV1@PBD@Z=004264a0
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0

// An animation type named by the entry, else the default (Westwood's
// CCINIClass::Get_AnimType is not recovered; written as a local reader).
static inline AnimTypeClass *Get_AnimType(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        return AnimTypeClass::Find_Or_Make(buffer);
    }
    return defvalue;
}

bool OverlayTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        char const *section = ID;
        Land = ini.Get_LandType(section, "Land", (LandType)Land);
        Strength = ini.Get_Int(section, "Strength", Strength);
        Wall = ini.Get_Bool(section, "Wall", Wall);
        Tiberium = ini.Get_Bool(section, "Tiberium", Tiberium);
        Crate = ini.Get_Bool(section, "Crate", Crate);
        CrateTrigger = ini.Get_Bool(section, "CrateTrigger", CrateTrigger);
        Explodes = ini.Get_Bool(section, "Explodes", Explodes);
        Overrides = ini.Get_Bool(section, "Overrides", Overrides);
        CellAnim = Get_AnimType(ini, section, "CellAnim", CellAnim);
        char const *image = unknown_1c8;
        DamageLevels = ArtINI.Get_Int(image, "DamageLevels", DamageLevels);
        DemandLoad = ArtINI.Get_Bool(image, "DemandLoad", DemandLoad);
        if (Tiberium) {
            unknown_9c = 6;
            if (Land == 0) {
                Land = 5;
            }
        }
        if (!unknown_1fc && !DemandLoad) {
            char fullname[512];
            _makepath(fullname, 0, 0, image, ".SHP");
            unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
        }
        NoUseTileLandType = ini.Get_Bool(section, "NoUseTileLandType", NoUseTileLandType);
        IsVeinholeMonster = ini.Get_Bool(section, "IsVeinholeMonster", IsVeinholeMonster);
        IsVeins = ini.Get_Bool(section, "IsVeins", IsVeins);
        ChainReaction = ini.Get_Bool(section, "ChainReaction", ChainReaction);
        DrawFlat = ini.Get_Bool(section, "DrawFlat", DrawFlat);
        IsARock = ini.Get_Bool(section, "IsARock", IsARock);
        IsRubble = ini.Get_Bool(section, "IsRubble", IsRubble);
        return true;
    }
    return false;
}
