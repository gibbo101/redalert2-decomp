// wchar_t const *SuperClass::State_String() const (0x0069D770)
// The sidebar caption for the super weapon's state, or null.

#include "shared/string_table.hpp"
// @ref ??_C@_08JP@TXT_HOLD?$AA@=007f3eb4
// @ref ??_C@_09IMGH@TXT_READY?$AA@=007d1610
// @ref ??_C@_0BB@CIBI@TXT_FIRESTORM_ON?$AA@=007f65cc
// @ref ??_C@_0BB@JFLP@D?3?2Ra2?2Super?4CPP?$AA@=007f65e0
// @ref ??_C@_0N@FBLE@TXT_CHARGING?$AA@=007f65bc
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0

wchar_t const *SuperClass::State_String() const
{
    if (!unknown_0x58) {
        if (Type->UseChargeDrain) {
            switch (unknown_0x60) {
            case 0:
                return StringTable::Load_String("TXT_CHARGING", 0, "D:\\Ra2\\Super.CPP", 0x32B);
            case 1:
                return StringTable::Load_String("TXT_READY", 0, "D:\\Ra2\\Super.CPP", 0x32E);
            case 2:
                return StringTable::Load_String("TXT_FIRESTORM_ON", 0, "D:\\Ra2\\Super.CPP", 0x331);
            default:
                return 0;
            }
        }
        if (unknown_0x57) {
            return StringTable::Load_String("TXT_READY", 0, "D:\\Ra2\\Super.CPP", 0x344);
        } else {
            return 0;
        }
    } else {
        return StringTable::Load_String("TXT_HOLD", 0, "D:\\Ra2\\Super.CPP", 0x34A);
    }
}
