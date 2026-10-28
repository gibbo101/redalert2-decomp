// Sets the local variable of a name (true when there is none; 0x006615B0).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

bool UnknownIDSource::Set_Local_Variable(char const *name, bool value)
{
    int index = Find_Local_Variable(name);
    if (index != -1) {
        return unknown_661560(index, value);
    }
    return true;
}
