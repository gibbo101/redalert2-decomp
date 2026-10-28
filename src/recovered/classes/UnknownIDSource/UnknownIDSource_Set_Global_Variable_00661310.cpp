// Sets the global variable of a name (true when there is none; 0x00661310).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

bool UnknownIDSource::Set_Global_Variable(char const *name, bool value)
{
    int index = Find_Global_Variable(name);
    if (index != -1) {
        return unknown_6612c0(index, value);
    }
    return true;
}
