#include "shared/radio.hpp"
int RadioClass::Unknown_00636E70(TechnoClass *techno) const {
    if (techno) {
        for (int index = 0; index < RadioLinks.Length(); ++index) {
            if (RadioLinks[index] == techno) return index;
        }
    }
    return -1;
}
