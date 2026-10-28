// TeamTypeClass *TargetClass::As_TeamType() const (0x006B5EC0): the indexed object if it is a TeamTypeClass, or null.
// @ref ___RTDynamicCast=00783ce4
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVAbstractClass@@@8=007ce240
// @ref ??_R0?AVTeamTypeClass@@@8=007f6d10
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?x@?1???A?$IndexClass@JPAVAbstractClass@@@@QBEABQAVAbstractClass@@ABJ@Z@4PAV2@A=00b2b628
// @ref _qsort=00781d46
// @ref ?search_compfunc@?$IndexClass@JPAVAbstractClass@@@@CAHPBX0@Z=0041ba10

TeamTypeClass *TargetClass::As_TeamType() const
{
    if (Kind == 0x34) {
        return dynamic_cast<TeamTypeClass *>(unknown_object_index_abff58[ID]);
    }
    return 0;
}
