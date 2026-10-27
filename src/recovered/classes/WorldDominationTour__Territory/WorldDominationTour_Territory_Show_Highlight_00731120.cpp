// void WorldDominationTour::Territory::Show_Highlight(bool arg, MSEngine *engine) (0x00731120)
// Passes arg to the highlight animation's slot 1, has the engine redraw its
// area and waits up to 300000 for the animation.
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

void Territory::Show_Highlight(bool arg, MSEngine *engine)
{
    if (HighlightAnim) {
        HighlightAnim->Set_Unknown_0C(arg);
        Rect rect = HighlightAnim->Get_Rect();
        engine->Broadcast((int)&rect);
        engine->Redraw();
        engine->Wait_For(HighlightAnim, 300000);
    }
}

}
