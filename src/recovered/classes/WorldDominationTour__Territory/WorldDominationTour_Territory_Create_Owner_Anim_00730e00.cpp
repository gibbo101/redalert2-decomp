// void WorldDominationTour::Territory::Create_Owner_Anim(MSEngine *engine, ConvertClass *drawer, Point2D const &offset) (0x00730E00)
// When the territory's shape file exists, creates its overlay animation at
// Origin + offset (frame -1), resets its slot-1 flag and adds it to the engine.
// The engine's animation list is passed as the overlay's int unknown_44
// (MSFadeAnim keeps it at +0x44; its type is not yet evidenced).
#include "shared/world_domination_tour.hpp"
#include "shared/cc_file_class.hpp"

namespace WorldDominationTour {

void Territory::Create_Owner_Anim(MSEngine *engine, ConvertClass *drawer, Point2D const &offset)
{
    int x = Origin.X + offset.X;
    int y = Origin.Y + offset.Y;
    CCFileClass file(ShapeName);
    if (file.Is_Available()) {
        OwnerAnim = new MSOverlayAnim(ShapeName, x, y, drawer, 0, (int)&engine->Anims, true, -1, false);
        OwnerAnim->Set_Unknown_0C(false);
        engine->Add_Anim(OwnerAnim);
    }
}

}
