#include "shared/radio.hpp"

bool RadioClass::Unknown_00636ED0(TechnoClass *techno) const {
    for (int index = 0; index < RadioLinks.Length(); ++index) {
        TechnoClass *contact = RadioLinks[index];
        if (!contact || contact == techno) return true;
    }
    return false;
}
