// The value of a global variable by name (false when there is none;
// 0x006613E0).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

bool UnknownIDSource::Get_Global_Variable(char const *name, bool *value)
{
    int index = Find_Global_Variable(name);
    if (index == -1) {
        return false;
    }
    return Get_Global_Variable(index, value);
}
