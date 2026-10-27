// int MapClass::Unknown_005500D0(Cell const &cell, int distance, int start) (0x005500D0)
// The first zone connection from start on whose +0x0C is 0 and whose
// straight segment (From..To, along Y when the X are equal, else along X)
// passes within distance of a cell; -1 when there is none.
#include "shared/map.hpp"
#include "shared/crt_memory.hpp"

int MapClass::Unknown_005500D0(Cell const &cell, int distance, int start)
{
    int index = start;
    int count = ZoneConnections.Count();
    for (; index < count; index++) {
        ZoneConnectionClass &connection = ZoneConnections[index];
        if (connection.unknown_0c == 0) {
            Cell from = connection.From;
            Cell to = connection.To;
            if (from.X - to.X == 0) {
                if (cell.Y >= from.Y && cell.Y <= to.Y && abs(cell.X - from.X) <= distance) {
                    return index;
                }
            } else {
                if (cell.X <= to.X && cell.X >= from.X && abs(cell.Y - from.Y) <= distance) {
                    return index;
                }
            }
        }
    }
    return -1;
}
