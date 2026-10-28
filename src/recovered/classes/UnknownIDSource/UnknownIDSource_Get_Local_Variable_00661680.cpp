// The value of a local variable by name (false when there is none;
// 0x00661680).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

bool UnknownIDSource::Get_Local_Variable(char const *name, bool *value)
{
    int index = Find_Local_Variable(name);
    if (index == -1) {
        return false;
    }
    return Get_Local_Variable(index, value);
}
