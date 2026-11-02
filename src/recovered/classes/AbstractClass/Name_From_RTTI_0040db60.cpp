// char const *__fastcall Name_From_RTTI(RTTIType rtti) (0x0040DB60)
// The name of an AbstractClass kind, "Unknown" when it is not in the table.
#include "shared/rtti_name_table.hpp"
// @ref ?RTTINames@@3PAURTTINameStruct@@A=007cd978
// @ref ??_C@_07PCHH@Unknown?$AA@=007cdbb0

char const *__fastcall Name_From_RTTI(RTTIType rtti)
{
    for (int index = 0; index < sizeof(RTTINames) / sizeof(RTTINames[0]); index++) {
        if (RTTINames[index].Type == rtti) {
            return RTTINames[index].Name;
        }
    }
    return "Unknown";
}
