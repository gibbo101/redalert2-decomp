// void InfantryClass::unknown_slot295() (0x00508820, slot 295)
// Unless the type is Fearless or check 13 (0x006D7910) holds: +0x5BC = 300
// (hypothesis: a fear counter).
#include "shared/infantry.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910

void InfantryClass::unknown_slot295()
{
    if (!Type->Fearless && !unknown_6d7910(13)) {
        unknown_5bc = 300;
    }
}
