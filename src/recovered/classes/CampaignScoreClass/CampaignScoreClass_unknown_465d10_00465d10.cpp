// void CampaignScoreClass::unknown_465d10() -- 0x00465D10
// Fills the session's score records from every house that is not multiplayer-passive: name,
// colour scheme, whether it won (and the last winner's record), the kills of each house's
// units and buildings, the totals lost and built, and the score; prints each record to the
// debug output. The records belong to the session object (the scheduling of the record and
// winner stores needs one object).
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ??_C@_05IOKF@Loser?$AA@=007d15e4
// @ref ??_C@_06POBF@Winner?$AA@=007d15ec
// @ref ??_C@_0ED@CLLE@?$CFs?3?5?$CFs?6?5Scheme?3?5?$CFd?6?5Lost?5?$DN?5?$CFd?6?5K@=007d15a0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Sum@UnknownHouseCounter@@QBEHXZ=00491d90
// @ref _wcscpy=00783689
// The unit's shape helpers fall back to unknown_static_rect (no empty rect of their own).
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/house.hpp"
#include "shared/debug_printf.hpp"
#include "shared/campaign_score.hpp"
#include "shared/session_state.hpp"

extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);

void CampaignScoreClass::unknown_465d10()
{
    unknown_session_a3d298.ScoreCount = 0;
    int count = Houses.Count();
    for (int i = 0; i < count; i++) {
        HouseClass *house = Houses[i];
        if (house != 0 && house->Type->MultiplayPassive != true) {
            int index = unknown_session_a3d298.ScoreCount++;
            unknown_session_a3d298.Scores[index].Winner = 0;
            wcscpy(unknown_session_a3d298.Scores[index].Name, house->UIName);
            unknown_session_a3d298.Scores[index].Lost = 0;
            unknown_session_a3d298.Scores[index].Kills = 0;
            unknown_session_a3d298.Scores[index].Built = 0;
            unknown_session_a3d298.Scores[index].Score = 0;
            unknown_session_a3d298.Scores[index].Scheme = house->ColorSchemeIndex;
            if (!house->unknown_13d) {
                unknown_session_a3d298.Scores[index].Winner++;
                unknown_session_a3d298.ScoreWinner = index;
            }
            int kills = 0;
            int j;
            for (j = 0; j < 20; j++) {
                kills += house->unknown_5310[j];
            }
            for (j = 0; j < count; j++) {
                kills += house->unknown_5364[j];
            }
            unknown_session_a3d298.Scores[index].Kills = kills;
            unknown_session_a3d298.Scores[index].Lost = house->unknown_5360 + house->unknown_53b4;
            int built = house->unknown_5460.Sum();
            built += house->unknown_5470.Sum();
            built += house->unknown_5480.Sum();
            built += house->unknown_5490.Sum();
            unknown_session_a3d298.Scores[index].Built = house->unknown_5360 + house->unknown_53b4 + built;
            if (house->unknown_5418 > 0) {
                unknown_session_a3d298.Scores[index].Score += house->unknown_5418;
            }
            Debug_Printf("%s: %s\n Scheme: %d\n Lost = %d\n Kills = %d\n Built = %d\n Score = %d\n",
                unknown_session_a3d298.Scores[index].Name,
                unknown_session_a3d298.Scores[index].Winner > 0 ? "Winner" : "Loser",
                unknown_session_a3d298.Scores[index].Scheme, unknown_session_a3d298.Scores[index].Lost,
                unknown_session_a3d298.Scores[index].Kills, unknown_session_a3d298.Scores[index].Built,
                unknown_session_a3d298.Scores[index].Score);
        }
    }
}
