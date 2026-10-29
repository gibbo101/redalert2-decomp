// void CampaignEndScoreClass::Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time,
//     int difficulty, int campaign, wchar_t const *name) -- 0x00467A20
// Copies the scores (sorted best first), time, difficulty, campaign and name for the end
// screen, loads its art and runs the dialog 0xBC7, then releases the art.
// @ref ?unknown_end_score_list_8504a8@@3PAPAVMPlayerScoreType@@A=008504a8
// @ref ?unknown_end_score_count_8504e8@@3HA=008504e8
// @ref ?unknown_end_score_time_85049c@@3HA=0085049c
// @ref ?unknown_end_score_difficulty_8504d0@@3HA=008504d0
// @ref ?unknown_end_score_campaign_850488@@3HA=00850488
// @ref ?unknown_end_score_name_850554@@3PAGA=00850554
// @ref ?unknown_end_score_dialog_proc_467330@@YGHPAUHWND__@@IIJ@Z=00467330
// @ref ?unknown_compare_descending_60_00465f20@@YAHPBX0@Z=00465f20
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_Load_Art_Once_006F2710@@YIXH@Z=006f2710
// @ref ?Unknown_Load_Art_Pair_006F2A30@@YIXH@Z=006f2a30
// @ref ?Unknown_006F2AB0@@YIXXZ=006f2ab0
// @ref ?Unknown_Free_Art_Flagged_006F2750@@YAXXZ=006f2750
// @ref ?unknown_dialog_box_5eab60@@YIHHP6GHPAUHWND__@@IIJ@Z_N@Z=005eab60
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref _wcscpy=00783689
// @ref _qsort=00781d46
// @ref ??3@YAXPAX@Z=00781d3b
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/id_source.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/campaign_score.hpp"

extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width, int (__cdecl *compare)(void const *, void const *));
int __cdecl unknown_compare_descending_60_00465f20(void const *left, void const *right);

void CampaignEndScoreClass::Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time, int difficulty,
    int campaign, wchar_t const *name)
{
    unknown_end_score_count_8504e8 = scores.Count();
    wcscpy(unknown_end_score_name_850554, name);
    for (int i = 0; i < unknown_end_score_count_8504e8; i++) {
        unknown_end_score_list_8504a8[i] = scores[i];
    }
    if (unknown_end_score_count_8504e8 > 1) {
        qsort(unknown_end_score_list_8504a8, unknown_end_score_count_8504e8, sizeof(MPlayerScoreType *),
            unknown_compare_descending_60_00465f20);
    }
    unknown_end_score_campaign_850488 = campaign;
    unknown_end_score_difficulty_8504d0 = difficulty;
    unknown_end_score_time_85049c = time;
    int alternate = unknown_id_source_a3d290->unknown_2239 == false;
    Unknown_Load_Art_Once_006F2710(alternate);
    Unknown_Load_Art_Pair_006F2A30(alternate);
    unknown_5159b0(0, true);
    unknown_dialog_box_5eab60(0xBC7, unknown_end_score_dialog_proc_467330, 0);
    Unknown_006F2AB0();
    Unknown_Free_Art_Flagged_006F2750();
}
