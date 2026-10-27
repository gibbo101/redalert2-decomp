// void MapClass::Unknown_005687B0(Rect const &rect) (0x005687B0)
// Collects every cell of a cell rectangle (X outer, Y inner) into a local
// vector and hands it to 0x005688A0.
#include "shared/map.hpp"
// @ref ?Unknown_005688A0@MapClass@@QAEXAAV?$DynamicVectorClass@VCell@@@@@Z=005688a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??3@YAXPAX@Z=00781d3b

void MapClass::Unknown_005687B0(Rect const &rect)
{
    DynamicVectorClass<Cell> cells;
    for (int x = rect.X; x < rect.X + rect.Width; x++) {
        for (int y = rect.Y; y < rect.Y + rect.Height; y++) {
            cells.Add(Cell(x, y));
        }
    }
    Unknown_005688A0(cells);
}
