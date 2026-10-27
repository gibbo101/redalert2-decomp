// void TEventClass::Build_INI_Entry(char *buffer) const (0x006E68B0)
#include "shared/object.hpp"

void TEventClass::Build_INI_Entry(char *buffer) const
{
    AbstractTypeClass *type = unknown_30;
    int data = Data;
    if (type != 0) {
        wsprintfA(buffer + strlen(buffer), "%d,%d,%s", Type, 1, (char const *)type->ID);
    } else {
        wsprintfA(buffer + strlen(buffer), "%d,%d,%d", Type, 0, data);
    }
}
