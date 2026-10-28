// The value of a global variable by index (false out of range; 0x006613B0).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

bool UnknownIDSource::Get_Global_Variable(int index, bool *value)
{
    if (index >= 0 && index < 50) {
        *value = Variables[index].Value;
        return true;
    }
    return false;
}
