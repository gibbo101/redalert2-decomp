// void WorldDominationTour::Map::unknown_72a620(MSEngine *engine, Voices *voices) (0x0072A620)
// With the +0x18 animation: says voice list 0 and waits for that animation (at most 300000 ms);
// then shows the +0x1C animation.
// @ref ?Say_List@Voices@WorldDominationTour@@QAEXH_NH@Z=00732700
// @ref ?Wait_For@MSEngine@@QAEXPAVMSAnim@@I@Z=005b2f30
#include "shared/wdt_map.hpp"
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Map::unknown_72a620(MSEngine *engine, Voices *voices)
{
    if (unknown_18) {
        voices->Say_List(0, true, 0);
        engine->Wait_For(unknown_18, 300000);
    }
    if (unknown_1c) {
        unknown_1c->Set_Unknown_0C(true);
    }
}

}
