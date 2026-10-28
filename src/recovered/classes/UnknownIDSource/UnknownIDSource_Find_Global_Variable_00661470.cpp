// The index of the global variable of a name, or -1 (0x00661470).
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

int UnknownIDSource::Find_Global_Variable(char const *name)
{
    for (int index = 0; index < 50; index++) {
        if (strcmp(name, Variables[index].unknown_00) == 0) {
            return index;
        }
    }
    return -1;
}
