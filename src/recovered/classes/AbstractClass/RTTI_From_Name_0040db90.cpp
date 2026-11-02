// RTTIType __fastcall RTTI_From_Name(char const *name) (0x0040DB90)
// The AbstractClass kind of a name (case-insensitive), RTTI_NONE when it is
// not in the table.
#include "shared/rtti_name_table.hpp"
#include "shared/crt_string.hpp"
// @ref ?RTTINames@@3PAURTTINameStruct@@A=007cd978

RTTIType __fastcall RTTI_From_Name(char const *name)
{
    for (int index = 0; index < sizeof(RTTINames) / sizeof(RTTINames[0]); index++) {
        if (_stricmp(RTTINames[index].Name, name) == 0) {
            return RTTINames[index].Type;
        }
    }
    return RTTI_NONE;
}
