#include "shared/radio.hpp"
bool RadioClass::Is_Radio_Contact(TechnoClass *techno) const {
    return Unknown_00636E70(techno) != -1;
}
