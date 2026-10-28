// The index of the local variable of a name, or -1 (0x00661710).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

int UnknownIDSource::Find_Local_Variable(char const *name)
{
    for (int index = 0; index < 50; index++) {
        if (strcmp(name, LocalVariables[index].unknown_00) == 0) {
            return index;
        }
    }
    return -1;
}
