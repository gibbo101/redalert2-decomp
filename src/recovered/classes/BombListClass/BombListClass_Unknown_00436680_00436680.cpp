// void BombListClass::Unknown_00436680(TechnoClass *techno) (0x00436680):
// joins the BombSight list (TechnoClass slot 53).
#include "shared/object.hpp"

void BombListClass::Unknown_00436680(TechnoClass *techno)
{
    unknown_18.Add(techno);
}
