// MP_Tally_Scores_005AABD0 (0x005AABD0): fills the session's score records from every house that is not
// multiplayer-passive or the player without a team (CampaignScoreClass::unknown_465d10's copy; built is the
// sum of the four counters at +0x54A0, and a house that did not lose gets a random bonus).

void MP_Tally_Scores_005AABD0()
{
    unknown_session_a3d298.ScoreCount = 0;
    int count = Houses.Count();
    for (int i = 0; i < count; i++) {
        HouseClass *house = Houses[i];
        if (house != 0 && house->Type->MultiplayPassive != true && house != unknown_house_a72d28) {
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
            unknown_session_a3d298.Scores[index].Lost = house->unknown_53b4 + house->unknown_5360;
            int built = house->unknown_54a0.Sum();
            built += house->unknown_54b0.Sum();
            built += house->unknown_54c0.Sum();
            built += house->unknown_54d0.Sum();
            unknown_session_a3d298.Scores[index].Built = built;
            if (house->unknown_5418 > 0) {
                unknown_session_a3d298.Scores[index].Score += house->unknown_5418;
            }
            if (!house->unknown_13d) {
                int score = unknown_session_a3d298.Scores[index].Score;
                unknown_session_a3d298.Scores[index].Score = Random_Pick(score / 2, score) + score / 2 + score;
            }
            Debug_Printf("%hs: %s\n Scheme: %d\n Lost = %d\n Kills = %d\n Built = %d\n Score = %d\n",
                unknown_session_a3d298.Scores[index].Name,
                unknown_session_a3d298.Scores[index].Winner > 0 ? "Winner" : "Loser",
                unknown_session_a3d298.Scores[index].Scheme, unknown_session_a3d298.Scores[index].Lost,
                unknown_session_a3d298.Scores[index].Kills, unknown_session_a3d298.Scores[index].Built,
                unknown_session_a3d298.Scores[index].Score);
        }
    }
}
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ??_C@_05IOKF@Loser?$AA@=007d15e4
// @ref ??_C@_06POBF@Winner?$AA@=007d15ec
// @ref ??_C@_0EE@NOMF@?$CFhs?3?5?$CFs?6?5Scheme?3?5?$CFd?6?5Lost?5?$DN?5?$CFd?6?5@=007e55cc
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Sum@UnknownHouseCounter@@QBEHXZ=00491d90
// @ref ?unknown_house_a72d28@@3PAVHouseClass@@A=00a72d28
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref _wcscpy=00783689
