// RulesClass::Movies (0x0064DC90)
// @ref _RulesSection_Movies=007a90a0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_06IJMO@Movies?$AA@=007eeba4
// Adds every movie named in [Movies] (a copy of the name) to the movie name
// list unless it is already there.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/ccini_extra.hpp"

extern "C" char *__cdecl _strdup(char const *string);

bool RulesClass::Movies(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_Movies)) {
        int count = ini.Entry_Count(RulesSection_Movies);
        for (int index = 0; index < count; index++) {
            char buffer[32];
            if (ini.Get_String(RulesSection_Movies, ini.Get_Entry(RulesSection_Movies, index), "<none>", buffer, sizeof(buffer))) {
                if (unknown_name_index_482e60(buffer) == -1) {
                    unknown_names_a71050.Add(_strdup(buffer));
                }
            }
        }
        return true;
    }
    return false;
}
