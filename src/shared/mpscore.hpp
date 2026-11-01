// MPScore.cpp (unit 0x005AA830-0x005AB3AF): the multiplayer and skirmish score screen (dialog 0x108). A
// copy of CampScor.cpp's score screen (shared/campaign_score.hpp): the scores are tallied from the houses
// into the session's records, sorted best first and shown one row per player. Names are hypotheses.
#ifndef RA2_SHARED_MPSCORE_HPP
#define RA2_SHARED_MPSCORE_HPP

struct HWND__;
class MPlayerScoreType;

// The sorted score records (0x00A715F0) and two values the screen's constructor clears (0x00A71684,
// 0x00A71688; nothing else reads them).
extern MPlayerScoreType *unknown_sorted_scores_a715f0[8];
extern int unknown_score_a71684;
extern int unknown_score_a71688;

// Per score row: the name, kills, lost, built and score controls (0x007E5518).
extern int unknown_mp_score_controls_7e5518[8][5];

// The time (seconds) as TXT_TIME_FORMAT_HOURS, capped at 99 hours (0x005AAAE0).
void __fastcall MP_Format_Time_005AAAE0(wchar_t *buffer, int time);
// Sends value as decimal text to the dialog control id (0x005AAB80).
void __fastcall MP_Set_Dialog_Item_Number_005AAB80(HWND__ *dialog, int id, int value);
// Fills the session's score records from the houses (0x005AABD0).
void MP_Tally_Scores_005AABD0();
// Sorts the records into unknown_sorted_scores_a715f0 (0x005AADD0).
void Unknown_005AADD0();
int __cdecl unknown_compare_descending_60_005aae10(void const *left, void const *right);
// The score dialog's procedure (0x005AAE40).
int __stdcall MP_Score_Dialog_Proc_005AAE40(HWND__ *window, unsigned int message, unsigned int wparam, long lparam);

#endif
