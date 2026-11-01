// void Unknown_005AADD0() (0x005AADD0)
// Sorts the session's used score records by their +0x60 value, largest first: fills the pointer table at
// 0x00A715F0 with &Scores[0..ScoreCount) and qsorts it with 0x005AAE10.
// @ref ?unknown_sorted_scores_a715f0@@3PAPAVMPlayerScoreType@@A=00a715f0
// @ref ?unknown_compare_descending_60_005aae10@@YAHPBX0@Z=005aae10
extern MPlayerScoreType *unknown_sorted_scores_a715f0[8];
int __cdecl unknown_compare_descending_60_005aae10(void const *left, void const *right);

void Unknown_005AADD0()
{
    int count = unknown_session_a3d298.ScoreCount;
    for (int index = 0; index < count; index++) {
        unknown_sorted_scores_a715f0[index] = &unknown_session_a3d298.Scores[index];
    }
    if (count > 1) {
        qsort(unknown_sorted_scores_a715f0, count, sizeof(MPlayerScoreType *), unknown_compare_descending_60_005aae10);
    }
}
