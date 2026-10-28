// The value of a local variable by index (false out of range; 0x00661650).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

bool UnknownIDSource::Get_Local_Variable(int index, bool *value)
{
    if (index >= 0 && index < 50) {
        *value = LocalVariables[index].Value;
        return true;
    }
    return false;
}
