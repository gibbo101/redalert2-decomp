// TargetClass::TargetClass(Cell const &cell) (0x006B5510): the cell; the zero
// cell (shared/unknown_geometry.hpp, this unit's copy) gives no target.
// @ref _unknown_geometry_k=00abff48

TargetClass::TargetClass(Cell const &cell)
{
    if (cell == unknown_geometry_k) {
        Kind = 0;
    } else {
        Kind = 11;
        ID = cell.X + cell.Y * 1000;
    }
}
