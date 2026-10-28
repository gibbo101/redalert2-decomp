// void SmudgeTypeClass::Place(Cell const &cell) const (0x00688B40)
// Marks every cell of the Width x Height block with this type and the
// cell's piece number (row * Width + column).
#include "shared/smudge_type.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_47c080@CellClass@@QAEXXZ=0047c080

void SmudgeTypeClass::Place(Cell const &cell) const
{
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            Cell pos = cell + Cell(x, y);
            CellClass &here = Map[pos];
            here.SmudgeIndex = ArrayIndex;
            here.SmudgeData = y * Width + x;
            here.unknown_47c080();
        }
    }
}
