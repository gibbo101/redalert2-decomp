// int __cdecl unknown_compare_descending_60(void const *, void const *) -- 0x005AAE10
// Purpose: qsort comparator over an array of object pointers, ordering by the
// int at +0x60 from largest to smallest (0 when equal). Referenced from 1
// data site (a qsort call). The pointee type is not yet identified.
struct UnknownSortItem_005aae10 {
    char unknown_00[0x60];
    int unknown_60;
};

int __cdecl unknown_compare_descending_60_005aae10(void const *left, void const *right)
{
    UnknownSortItem_005aae10 const *a = *(UnknownSortItem_005aae10 const * const *)left;
    UnknownSortItem_005aae10 const *b = *(UnknownSortItem_005aae10 const * const *)right;
    if (a->unknown_60 == b->unknown_60) {
        return 0;
    }
    return a->unknown_60 > b->unknown_60 ? -1 : 1;
}
