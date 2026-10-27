// bool AbstractTypeClass::Write_INI(CCINIClass &ini) const (0x00410910)
// Rewrites the section: Name=, and UIName= when set.
#include "shared/abstract_type.hpp"
// @ref ??_C@_06BMKI@UIName?$AA@=007ce29c
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4

bool AbstractTypeClass::Write_INI(CCINIClass &ini) const
{
    ini.Clear(ID);
    ini.Put_String(ID, "Name", Name);
    if (UINameLabel[0] != 0) {
        ini.Put_String(ID, "UIName", UINameLabel);
    }
    return true;
}
