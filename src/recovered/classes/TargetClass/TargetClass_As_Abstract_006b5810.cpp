// AbstractClass *TargetClass::As_Abstract() const (0x006B5810): the indexed
// object or the cell, or null.
// @ref ___RTDynamicCast=00783ce4
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVAbstractClass@@@8=007ce240
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?x@?1???A?$IndexClass@JPAVAbstractClass@@@@QBEABQAVAbstractClass@@ABJ@Z@4PAV2@A=00b2b628
// @ref _qsort=00781d46
// @ref ?search_compfunc@?$IndexClass@JPAVAbstractClass@@@@CAHPBX0@Z=0041ba10
// @ref ?Binary_Search@@YIPAUNodeElement@?$IndexClass@JPAVAbstractClass@@@@PAU12@HABU12@@Z=005098e0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070

AbstractClass *TargetClass::As_Abstract() const
{
    if (Kind == 0x34) {
        return dynamic_cast<AbstractClass *>(unknown_object_index_abff58[ID]);
    }
    if (Kind == 11) {
        return &Map[Cell(ID % 1000, ID / 1000)];
    }
    return 0;
}
