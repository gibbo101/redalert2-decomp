// void TechnoClass::Unknown_006D9610(AbstractClass *cell) (0x006D9610)
// Re-registers the techno with a cell: takes the old +0x400 value back
// (0x006D95D0) and records slot 168's current value (0x006D95A0).
#include "shared/techno.hpp"
// @ref ?unknown_476b20@UnknownCellClass@@QAEXHH@Z=00476b20

void TechnoClass::Unknown_006D9610(AbstractClass *cell)
{
    if (cell != 0) {
        unknown_6d95d0((UnknownCellClass *)cell);
        unknown_6d95a0((UnknownCellClass *)cell);
    }
}
