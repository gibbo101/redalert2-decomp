#include "shared/map.hpp"

int MapClass::Unknown_0054FAB0(Cell const &cell)
{
    int index = Unknown_0054FAF0(cell);
    int result;
    if (index < 0) {
        result = 0;
    } else if (index >= unknown_68) {
        result = unknown_68 - 1;
    } else {
        result = index;
    }
    return result;
}
