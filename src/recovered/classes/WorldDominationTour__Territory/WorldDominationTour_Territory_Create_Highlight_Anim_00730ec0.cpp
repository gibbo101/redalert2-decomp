// void WorldDominationTour::Territory::Create_Highlight_Anim(MSEngine *engine, ConvertClass *drawer, Point2D const &offset) (0x00730EC0)
// When the territory's shape file exists, creates its overlay animation at
// Origin + offset (frame 0), resets its slot-1 flag and adds it to the engine.
// The overlay redraws the engine's other animations over each step.
#include "shared/world_domination_tour.hpp"
#include "shared/cc_file_class.hpp"

namespace WorldDominationTour {

void Territory::Create_Highlight_Anim(MSEngine *engine, ConvertClass *drawer, Point2D const &offset)
{
    int x = Origin.X + offset.X;
    int y = Origin.Y + offset.Y;
    CCFileClass file(ShapeName);
    if (file.Is_Available()) {
        HighlightAnim = new MSOverlayAnim(ShapeName, x, y, drawer, 0, &engine->Anims, true, 0, false);
        HighlightAnim->Set_Unknown_0C(false);
        engine->Add_Anim(HighlightAnim);
    }
}

}
