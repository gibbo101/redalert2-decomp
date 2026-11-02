// CCINIClass::Put_PipScale (0x00469E70): writes a pip scale by name; none (0) is not written
// (TibSun Put_PipScaleType).
#include "shared/ccini_class.hpp"
#include "shared/ccini_extra.hpp"
// @ref ?PipScaleNames@@3PAUNameValueStruct@@A=007d1998

bool CCINIClass::Put_PipScale(char const *section, char const *entry, int scale)
{
    if (scale != 0) {
        return Put_String(section, entry, PipScaleNames[scale].Name);
    }
    return false;
}
