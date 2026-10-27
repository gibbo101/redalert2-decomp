// void MapClass::Unknown_00564B20(int arg) (0x00564B20)
// Runs 0x00564B60 with arg on every zone connection whose +0x08 is set.
#include "shared/map.hpp"
// @ref ?Unknown_00564B60@MapClass@@QAEXPAUZoneConnectionClass@@H@Z=00564b60

void MapClass::Unknown_00564B20(int arg)
{
    for (int index = 0; index < ZoneConnections.Count(); index++) {
        ZoneConnectionClass &connection = ZoneConnections[index];
        if (connection.unknown_08) {
            Unknown_00564B60(&connection, arg);
        }
    }
}
