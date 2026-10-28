// CellClass *TargetClass::As_Cell() const (0x006B6610): the cell, or null.
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070

CellClass *TargetClass::As_Cell() const
{
    if (Kind == 11) {
        return &Map[Cell(ID % 1000, ID / 1000)];
    }
    return 0;
}
