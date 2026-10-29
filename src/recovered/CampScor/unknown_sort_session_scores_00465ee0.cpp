// void unknown_sort_session_scores() -- 0x00465EE0
// Points the score list at the session's records and sorts them best first.
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_score_list_850448@@3PAPAVMPlayerScoreType@@A=00850448
// @ref ?unknown_compare_descending_60_00465f20@@YAHPBX0@Z=00465f20
// @ref _qsort=00781d46
#include "shared/unknown_globals.hpp"
#include "shared/campaign_score.hpp"

extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width, int (__cdecl *compare)(void const *, void const *));
int __cdecl unknown_compare_descending_60_00465f20(void const *left, void const *right);

void unknown_sort_session_scores_465ee0()
{
    int count = unknown_session_a3d298.ScoreCount;
    for (int i = 0; i < count; i++) {
        unknown_score_list_850448[i] = &unknown_session_a3d298.Scores[i];
    }
    if (count > 1) {
        qsort(unknown_score_list_850448, count, sizeof(MPlayerScoreType *), unknown_compare_descending_60_00465f20);
    }
}
