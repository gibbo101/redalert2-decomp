// bool __fastcall Unknown_006F5E80(int group) (0x006F5E80)
// Whether the player-side technos of the map that are in group (group - 1 at +0x1AC) are exactly
// the selected ones.
#include "shared/uicmnds.hpp"

bool __fastcall Unknown_006F5E80(int group)
{
    for (int index = Technos.Count() - 1; index >= 0; index--) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && !techno->unknown_76 && Is_Player_Side(techno)) {
            if (techno->unknown_1ac == group - 1 && !techno->unknown_77) {
                return false;
            }
            if (techno->unknown_1ac != group - 1 && techno->unknown_77) {
                return false;
            }
        }
    }
    return true;
}
