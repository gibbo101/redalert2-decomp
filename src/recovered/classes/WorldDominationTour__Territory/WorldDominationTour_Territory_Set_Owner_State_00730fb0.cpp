// void WorldDominationTour::Territory::Set_Owner_State(int state, MSEngine *engine, bool wait) (0x00730FB0)
// TibSun wdtterr.cpp shape: picks the owner overlay frame (state 1-3 -> 3-1),
// restarts or hides the overlay, redraws the union of the old and new
// overlay rectangles and runs the engine for one frame (wait is unused).
// @ref ?Set_Frame@MSOverlayAnim@@QAEXI@Z=0x005AD820
// @ref ?Restart@MSOverlayAnim@@QAEXXZ=0x005AD810
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

void Territory::Set_Owner_State(int state, MSEngine *engine, bool wait)
{
    if (OwnerAnim != 0) {
        int frame = -1;
        switch (state) {
            case 1:
                frame = 3;
                break;
            case 2:
                frame = 2;
                break;
            case 3:
                frame = 1;
                break;
        }
        Rect oldrect = OwnerAnim->Get_Rect();
        if (frame >= 0) {
            OwnerAnim->Set_Frame(frame);
            OwnerAnim->Set_Unknown_0C(true);
            OwnerAnim->Restart();
        } else {
            OwnerAnim->Set_Unknown_0C(false);
        }
        Rect newrect = OwnerAnim->Get_Rect();
        Rect rect = Union(newrect, oldrect);
        engine->Broadcast((int)&rect);
        engine->Redraw();
        engine->Run(1);
    }
}

}
