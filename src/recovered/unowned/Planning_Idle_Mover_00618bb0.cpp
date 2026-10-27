#define RA2_COORD_EQUAL_MEMBER
// bool __fastcall Planning_Idle_Mover(TechnoClass *techno) (0x00618BB0)
// Whether a moving techno (mission 0xB) has no destination object yet.
#include "shared/planning.hpp"
#include "shared/foot.hpp"

bool __fastcall Planning_Idle_Mover(TechnoClass *techno)
{
    if (techno->unknown_slot91() == 0x0B) {
        bool flagged;
        if (techno) {
            flagged = techno->unknown_14_bit2;
        }
        if (techno && flagged) {
            if (((FootClass *)techno)->unknown_494 || techno->unknown_228) {
                return false;
            }
        }
        return true;
    }
    return false;
}
