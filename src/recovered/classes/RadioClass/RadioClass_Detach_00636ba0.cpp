// void RadioClass::Detach(AbstractClass *target, bool all) (0x00636BA0, slot 10)
// MissionClass's part, then forgets the target among the radio contacts
// (only when all).
#include "shared/radio.hpp"
#include "shared/techno.hpp"
// @ref ?Detach@ObjectClass@@UAEXPAVAbstractClass@@_N@Z=005d3bd0

void RadioClass::Detach(AbstractClass *target, bool all)
{
    MissionClass::Detach(target, all);
    for (int index = 0; index < RadioLinks.Length(); index++) {
        if (RadioLinks[index] == (TechnoClass *)target && all) {
            RadioLinks[index] = 0;
        }
    }
}
