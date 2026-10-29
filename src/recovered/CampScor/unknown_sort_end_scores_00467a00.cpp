// void unknown_sort_end_scores() -- 0x00467A00
// Sorts the end screen's score list best first.
// @ref ?unknown_end_score_list_8504a8@@3PAPAVMPlayerScoreType@@A=008504a8
// @ref ?unknown_end_score_count_8504e8@@3HA=008504e8
// @ref ?unknown_compare_descending_60_00465f20@@YAHPBX0@Z=00465f20
// @ref _qsort=00781d46
#include "shared/campaign_score.hpp"

extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width, int (__cdecl *compare)(void const *, void const *));
int __cdecl unknown_compare_descending_60_00465f20(void const *left, void const *right);

void unknown_sort_end_scores_467a00()
{
    if (unknown_end_score_count_8504e8 > 1) {
        qsort(unknown_end_score_list_8504a8, unknown_end_score_count_8504e8, sizeof(MPlayerScoreType *),
            unknown_compare_descending_60_00465f20);
    }
}
