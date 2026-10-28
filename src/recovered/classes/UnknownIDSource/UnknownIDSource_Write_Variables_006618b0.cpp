// bool UnknownIDSource::Write_Variables(CCINIClass &ini) (0x006618B0)
// Rewrites [VariableNames]: each named local variable as "index=name,value".
// Always true.
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_05LOBO@?$CFs?0?$CFd?$AA@=007f2390
// @ref __imp__wsprintfA=0079a4a4
#include "shared/id_source.hpp"
#include "shared/ccini_class.hpp"
#include "shared/win32_api.hpp"

bool UnknownIDSource::Write_Variables(CCINIClass &ini)
{
    ini.Clear(unknown_variable_names_section_7a9200);
    for (int index = 0; index < 50; index++) {
        UnknownScenarioVariable_004B5AB0 &variable = LocalVariables[index];
        if (variable.unknown_00[0] != 0) {
            char entry[12];
            char value[128];
            wsprintfA(entry, "%d", index);
            wsprintfA(value, "%s,%d", variable.unknown_00, variable.Value != 0);
            ini.Put_String(unknown_variable_names_section_7a9200, entry, value);
        }
    }
    return true;
}
