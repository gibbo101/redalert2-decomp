// bool __fastcall unknown_matches_any_name(UnknownObject_006f7610 *object, UnknownNameList_006f7610 const &names) -- 0x006F7610
// Purpose: whether the object's type ID matches any of the names (the
// ObjectClass test 0x005D27D0 for each).
// Assumptions: the list is a DynamicVectorClass of names (elements at
// +0x04, count at +0x10); views only.
// @ref ?unknown_func_5d27d0@UnknownObject_006f7610@@QBE_NPBD@Z=005d27d0

struct UnknownObject_006f7610 {
    bool unknown_func_5d27d0(char const *name) const;   // 0x005D27D0
};
struct UnknownNameList_006f7610 {
    void *vtable_00;
    char const **Vector;                    // +0x04
    int VectorMax;
    int unknown_0c;
    int ActiveCount;                        // +0x10
};

bool __fastcall unknown_matches_any_name(UnknownObject_006f7610 *object, UnknownNameList_006f7610 const &names)
{
    int count = names.ActiveCount;
    for (int index = 0; index < count; index++) {
        char const *name = names.Vector[index];
        if (object->unknown_func_5d27d0(name)) {
            return true;
        }
    }
    return false;
}
