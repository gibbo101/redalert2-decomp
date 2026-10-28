// void LaserDrawClass::Update() (0x00533330)
#include "shared/laser_draw_list.hpp"

void LaserDrawClass::Update()
{
    Progress.Advance_Stage_When_Ready();
    if (Blinks) {
        BlinkState = !BlinkState;
    }
    if (Progress.Stage >= Duration) {
        delete this;
    }
}
