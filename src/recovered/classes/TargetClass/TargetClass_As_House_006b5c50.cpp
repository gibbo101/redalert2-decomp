// HouseClass *TargetClass::As_House() const (0x006B5C50): the indexed object if it is a HouseClass, or null.
// @ref ___RTDynamicCast=00783ce4
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVAbstractClass@@@8=007ce240
// @ref ??_R0?AVHouseClass@@@8=007da1a8
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?x@?1???A?$IndexClass@JPAVAbstractClass@@@@QBEABQAVAbstractClass@@ABJ@Z@4PAV2@A=00b2b628
// @ref _qsort=00781d46
// @ref ?search_compfunc@?$IndexClass@JPAVAbstractClass@@@@CAHPBX0@Z=0041ba10

HouseClass *TargetClass::As_House() const
{
    if (Kind == 0x34) {
        return dynamic_cast<HouseClass *>(unknown_object_index_abff58[ID]);
    }
    return 0;
}
