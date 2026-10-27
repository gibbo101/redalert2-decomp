// int MapClass::Unknown_0054E370(Cell const &cell) (0x0054E370)
// The index of the cell's 4 x 4 block in a 130 x 130 grid that keeps a
// one-block border (the layout of HouseClass +0x56D0).
#include "shared/map.hpp"

int MapClass::Unknown_0054E370(Cell const &cell)
{
    return (cell.Y / 4 + 1) * 130 + (cell.X / 4 + 1);
}
