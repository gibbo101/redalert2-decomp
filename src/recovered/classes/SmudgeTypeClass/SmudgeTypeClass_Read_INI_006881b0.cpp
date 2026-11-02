// bool SmudgeTypeClass::Read_INI(CCINIClass &ini) (0x006881B0)
// Reads "Crater", "Burn", "Width" and "Height", then loads the image (the
// theater variant for theater-specific types, else the .SHP file).
#include "shared/smudge_type.hpp"
// @ref ??_C@_06NEFL@Crater?$AA@=007cefac
// @ref ??_C@_04IGJJ@Burn?$AA@=007f4280
// @ref ??_C@_05PJLH@Width?$AA@=007e169c
// @ref ??_C@_06FOPC@Height?$AA@=007d0bf0
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0

bool SmudgeTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        char const *section = ID;
        Crater = ini.Get_Bool(section, "Crater", Crater);
        Burn = ini.Get_Bool(section, "Burn", Burn);
        Width = ini.Get_Int(section, "Width", Width);
        Height = ini.Get_Int(section, "Height", Height);
        char fullname[512];
        if (!unknown_1fc) {
            _makepath(fullname, 0, 0, unknown_1c8, ".SHP");
        } else {
            _makepath(fullname, 0, 0, unknown_1c8, Theaters[unknown_id_source_a3d290->Theater].Suffix);
        }
        unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
        return true;
    }
    return false;
}
