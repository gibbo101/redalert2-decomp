// TechnoClass *TargetClass::As_Techno() const (0x006B5910): the indexed object
// as a techno (AbstractClass::As_Techno), or null.
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?x@?1???A?$IndexClass@JPAVAbstractClass@@@@QBEABQAVAbstractClass@@ABJ@Z@4PAV2@A=00b2b628
// @ref _qsort=00781d46
// @ref ?search_compfunc@?$IndexClass@JPAVAbstractClass@@@@CAHPBX0@Z=0041ba10
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20

TechnoClass *TargetClass::As_Techno() const
{
    if (Kind == 0x34) {
        return unknown_object_index_abff58[ID]->As_Techno();
    }
    return 0;
}
