// void TechnoClass::unknown_slot119(int mission, int unknown2, int unknown3) (0x006CD840, slot 119)
// Remembers +0x228 in +0x22C, then the mission override and slot 220.
#include "shared/techno.hpp"
// @ref ?unknown_slot119@MissionClass@@UAEXHHH@Z=00594d20

void TechnoClass::unknown_slot119(int mission, int unknown2, int unknown3)
{
    unknown_22c = unknown_228;
    MissionClass::unknown_slot119(mission, unknown2, unknown3);
    unknown_slot220((AbstractClass *)unknown2);   // the mission target (MissionClass slot 119 still declares it int)
}
