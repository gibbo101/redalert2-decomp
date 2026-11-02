// DynamicVectorClass<ColorScheme *> *SchemeTable::Find_Schemes(char const *name) (0x006044A0; no direct callers):
// the scheme list filed under the palette name, null when there is none (the table's Find expands inline; the
// key is a named HashString local).
#include "shared/scheme_table.hpp"

DynamicVectorClass<ColorScheme *> *SchemeTable::Find_Schemes(char const *name)
{
    HashString key(name);
    SchemeNode **node = Table->Find(key);
    if (node == 0) {
        return 0;
    }
    return (*node)->Schemes;
}
