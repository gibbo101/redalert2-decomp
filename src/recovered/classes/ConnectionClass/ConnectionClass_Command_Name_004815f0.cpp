// char *__fastcall ConnectionClass::Command_Name(int command) (0x004815F0)
// The name of a packet code, or null.
#include "shared/connection.hpp"
// @ref ?Commands@ConnectionClass@@2PAPADA=007d30dc

char *__fastcall ConnectionClass::Command_Name(int command)
{
    if (command >= 0 && command < PACKET_COUNT) {
        return Commands[command];
    }
    return 0;
}
