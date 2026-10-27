// bool AbstractTypeClass::Read_INI(CCINIClass &ini) (0x004107E0)
// Reads Name= and UIName= from the type's section; false without one.
#include "shared/abstract_type.hpp"
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ??_C@_0BD@BIBO@D?3?2Ra2?2AbsType?4cpp?$AA@=007ce288
// @ref ??_C@_06BMKI@UIName?$AA@=007ce29c
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4

bool AbstractTypeClass::Read_INI(CCINIClass &ini)
{
    char buffer[1024];

    if (ini.Find_Section(ID)) {
        ini.Get_String(ID, "Name", Name, buffer, sizeof(Name));
        Name = buffer;
        ini.Get_String(ID, "UIName", UINameLabel, buffer, sizeof(UINameLabel));
        UINameLabel = buffer;
        if (UINameLabel[0] != 0) {
            UIName = StringTable::Load_String(UINameLabel, 0, "D:\\Ra2\\AbsType.cpp", 205);
        } else {
            UIName = unknown_empty_wide_839d4c;
        }
        return true;
    }
    return false;
}
