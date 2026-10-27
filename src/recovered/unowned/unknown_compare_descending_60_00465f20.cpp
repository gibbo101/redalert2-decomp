// int __cdecl unknown_compare_descending_60(void const *, void const *) -- 0x00465F20
// Purpose: qsort comparator over an array of object pointers, ordering by the
// int at +0x60 from largest to smallest (0 when equal). Referenced from 4
// data sites (qsort calls). The pointee type is not yet identified.
struct UnknownSortItem_00465f20 {
    char unknown_00[0x60];
    int unknown_60;
};

int __cdecl unknown_compare_descending_60_00465f20(void const *left, void const *right)
{
    UnknownSortItem_00465f20 const *a = *(UnknownSortItem_00465f20 const * const *)left;
    UnknownSortItem_00465f20 const *b = *(UnknownSortItem_00465f20 const * const *)right;
    if (a->unknown_60 == b->unknown_60) {
        return 0;
    }
    return a->unknown_60 > b->unknown_60 ? -1 : 1;
}
