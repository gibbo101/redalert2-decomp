// TechnoClass *FootClass::unknown_slot299(DynamicVectorClass<TechnoTypeClass *> const *types, int arg2, int arg3) (0x004CD920)
// Slot 300 for each type; keeps the result with the lowest score, or a
// later one whose +0x32B is set, or any when the best score is -1.
#include "shared/foot.hpp"

TechnoClass *FootClass::unknown_slot299(DynamicVectorClass<TechnoTypeClass *> const *types, int arg2, int arg3)
{
    TechnoClass *best = 0;
    int best_score = -1;
    for (int index = 0; index < types->Count(); index++) {
        int score = -1;
        TechnoClass *found = unknown_slot300((*types)[index], arg2, arg3, &score);
        if (found != 0) {
            if (best == 0 || score < best_score || best_score == -1 || found->unknown_32b) {
                best = found;
                best_score = score;
            }
        }
    }
    return best;
}
