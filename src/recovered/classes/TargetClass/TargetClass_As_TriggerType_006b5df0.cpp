// TriggerTypeClass *TargetClass::As_TriggerType() const (0x006B5DF0): the indexed object if it is a TriggerTypeClass, or null.
// @ref ___RTDynamicCast=00783ce4
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVAbstractClass@@@8=007ce240
// @ref ??_R0?AVTriggerTypeClass@@@8=007f6cf0
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?x@?1???A?$IndexClass@JPAVAbstractClass@@@@QBEABQAVAbstractClass@@ABJ@Z@4PAV2@A=00b2b628
// @ref _qsort=00781d46
// @ref ?search_compfunc@?$IndexClass@JPAVAbstractClass@@@@CAHPBX0@Z=0041ba10

TriggerTypeClass *TargetClass::As_TriggerType() const
{
    if (Kind == 0x34) {
        return dynamic_cast<TriggerTypeClass *>(unknown_object_index_abff58[ID]);
    }
    return 0;
}
