// The cooperative campaign score screens (RTTI CampaignScoreClass, vtable 0x0079D724,
// 8 bytes; CampaignEndScoreClass, vtable 0x0079D730, 4 bytes). Each has a virtual
// destructor and one virtual that shows the screen for the players' scores.
#ifndef RA2_SHARED_CAMPAIGN_SCORE_HPP
#define RA2_SHARED_CAMPAIGN_SCORE_HPP

#include "shared/vector_class.hpp"
#include "shared/mplayer_score_type.hpp"

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

// Shown after each cooperative campaign map.
class CampaignScoreClass {
public:
    CampaignScoreClass();                                        // 0x00465BF0
    virtual ~CampaignScoreClass();                               // 0x00465C10 (scalar deleting 0x00467B00)
    // Shows the map's scores: the game time, whether more maps follow, the difficulty
    // (0-2, -1 unknown) and the campaign name.
    virtual void Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time, bool more,
        int difficulty, wchar_t const *name);                    // 0x00466A50

    // Fills the session's score records from the houses (0x00465D10).
    void unknown_465d10();

    int unknown_04;                                              // +0x04
};

// Shown when the cooperative campaign ends.
class CampaignEndScoreClass {
public:
    CampaignEndScoreClass();                                     // 0x00467200
    virtual ~CampaignEndScoreClass();                            // 0x00467230 (scalar deleting 0x00467B20)
    // Shows the campaign's total scores: the time, the difficulty, the campaign type + 1
    // and the campaign name.
    virtual void Presentation(DynamicVectorClass<MPlayerScoreType *> scores, int time, int difficulty,
        int campaign, wchar_t const *name);                      // 0x00467A20
};

// Set by the score screens (read and cleared by MPCooperative slot 36; 0x00850504).
extern bool unknown_score_850504;
// The shown map's game time (CampaignScoreClass::Presentation; 0x00850508).
extern int unknown_score_time_850508;
// The shown map's difficulty, -1 when unknown (CampaignScoreClass::Presentation; 0x007D1480).
extern int unknown_score_difficulty_7d1480;
// The map's scores the screen shows, best first (0x00850448).
extern MPlayerScoreType *unknown_score_list_850448[];
// Which players are ready to continue (0x008504C8; the screen's player rows).
extern bool unknown_score_ready_8504c8[8];

// Formats a game time in seconds as hours, minutes and seconds (TXT_TIME_FORMAT_HOURS;
// at most 99:59:59); does nothing without a buffer (0x00465C20).
void __fastcall unknown_format_time_465c20(wchar_t *buffer, int time);
// Points the score list at the session's records and sorts them best first (0x00465EE0).
void unknown_sort_session_scores_465ee0();
// Marks every player row ready, then the first count rows not ready (0x00465F50).
void __fastcall unknown_reset_ready_465f50(int count);
// Whether every player row is ready (0x00465F80).
bool unknown_all_ready_465f80();
// Sets or reads one player row's ready state (0x00465FA0, 0x00465FB0).
void __fastcall unknown_set_ready_465fa0(int index, bool ready);
bool __fastcall unknown_is_ready_465fb0(int index);

// The campaign end screen's state (0x008504A8 list, 0x008504E8 count, 0x0085049C time,
// 0x008504D0 difficulty (-1 unknown), 0x00850488 campaign, 0x00850554 name).
extern MPlayerScoreType *unknown_end_score_list_8504a8[];
extern int unknown_end_score_count_8504e8;
extern int unknown_end_score_time_85049c;
extern int unknown_end_score_difficulty_8504d0;
extern int unknown_end_score_campaign_850488;
extern wchar_t unknown_end_score_name_850554[];
// The end screen's copy of unknown_format_time_465c20 (0x00467290).
void __fastcall unknown_format_time_467290(wchar_t *buffer, int time);
// The end screen's dialog procedure (0x00467330).
int __stdcall unknown_end_score_dialog_proc_467330(struct HWND__ *window, unsigned int message, unsigned int wparam, long lparam);

// The score screens' art (shared/ unowned sources 0x006F2710, 0x006F2A30, 0x006F2AB0, 0x006F2750).
void __fastcall Unknown_Load_Art_Once_006F2710(int alternate);
void __fastcall Unknown_Load_Art_Pair_006F2A30(int alternate);
void __fastcall Unknown_006F2AB0();
void Unknown_Free_Art_Flagged_006F2750();
// Runs a modal dialog from a resource with a dialog procedure; returns its result (0x005EAB60).
int __fastcall unknown_dialog_box_5eab60(int resource, int (__stdcall *proc)(struct HWND__ *, unsigned int, unsigned int, long), int unknown3);

#endif
