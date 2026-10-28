// void BombListClass::Unknown_004366D0(TechnoClass *techno) (0x004366D0):
// leaves the BombSight list (TechnoClass slot 52).
#include "shared/object.hpp"

void BombListClass::Unknown_004366D0(TechnoClass *techno)
{
    unknown_18.Delete(techno);
}
