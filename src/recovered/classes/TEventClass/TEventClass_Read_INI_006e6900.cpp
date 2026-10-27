// void TEventClass::Read_INI() (0x006E6900)
// Reads "type,kind,value" from the current strtok position: kind 0 keeps
// the value as a number, kind 1 as a named type.
#include "shared/object.hpp"

void TEventClass::Read_INI()
{
    Data = 0;
    Type = atoi(strtok(0, ","));
    int kind = atoi(strtok(0, ","));
    char *token = strtok(0, ",");
    int value = atoi(token);
    switch (kind) {
    case 0:
        Data = value;
        break;
    case 1:
        unknown_30 = Unknown_006BF260(token);
        break;
    }
}
