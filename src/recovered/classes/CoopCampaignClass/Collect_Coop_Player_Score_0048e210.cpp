// void __fastcall Collect_Coop_Player_Score_0048e210(MPlayerScoreType &output, bool skip_first) (0x0048E210)
// Fills a score record from the first (or, with skip_first, the second) active
// non-passive player house.
#include "shared/coop_campaign.hpp"
// @ref ??_C@_0EI@HLKF@?$EA?$EA?$EA?$EA?5?$CFs?3?5?$CFs?6?5Scheme?3?5?$CFd?6?5Lost?5?$DN?5@=007d4e8c
// @ref ??_C@_06POBF@Winner?$AA@=007d15ec
// @ref ??_C@_05IOKF@Loser?$AA@=007d15e4
#include "shared/mplayer_score_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_player_entry.hpp"

void __fastcall Collect_Coop_Player_Score_0048e210(MPlayerScoreType &output, bool skip_first)
{
    int count = Houses.Count();
    for (int index = 0; index < count; index++) {
        HouseClass *house = Houses[index];
        if (house != 0 && house->Type->MultiplayPassive != true && house->unknown_134) {
            if (!skip_first) {
                output.Winner = 0;
                wcscpy(output.Name, house->UIName);
                output.Lost = 0;
                output.Kills = 0;
                output.Built = 0;
                output.Score = 0;
                output.Scheme = house->ColorSchemeIndex;
                if (!house->unknown_13d) {
                    output.Winner++;
                }
                int kills = 0;
                int i;
                for (i = 0; i < 20; i++) {
                    kills += house->unknown_5310[i];
                }
                for (i = 0; i < count; i++) {
                    kills += house->unknown_5364[i];
                }
                output.Kills = kills;
                output.Lost = house->unknown_5360 + house->unknown_53b4;
                int built = house->unknown_5460.Sum();
                built += house->unknown_5470.Sum();
                built += house->unknown_5480.Sum();
                built += house->unknown_5490.Sum();
                output.Built = house->unknown_5360 + house->unknown_53b4 + built;
                if (house->unknown_5418 > 0) {
                    output.Score += house->unknown_5418;
                }
                char const *result = output.Winner > 0 ? "Winner" : "Loser";
                char *name = Unknown_006FA120(output.Name);
                Debug_Printf("@@@@ %s: %s\n Scheme: %d\n Lost = %d\n Kills = %d\n Built = %d\n Score = %d\n",
                             name, result, output.Scheme,
                             output.Lost, output.Kills, output.Built, output.Score);
                return;
            }
            skip_first = false;
        }
    }
}
