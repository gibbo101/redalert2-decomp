// void Voices::Anim::Draw(Surface *surface, Rect const *clip) (0x00732BD0)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Anim::Draw(Surface *surface, Rect const *clip)
{
    Owner->Update();
}

}
