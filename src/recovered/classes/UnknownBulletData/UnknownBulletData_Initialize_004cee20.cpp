// void UnknownBulletData::Initialize_004cee20(CoordStruct const &from, CoordStruct const &to, int arm, int max) (0x004CEE20)
// Starts both timers (the first runs at least as long as the second), keeps the
// target coordinate and its distance from the start.
#include "shared/bullet.hpp"
#include "shared/coord_distance.hpp"

void UnknownBulletData::Initialize_004cee20(CoordStruct const &from, CoordStruct const &to, int arm, int max)
{
    if (max <= arm) {
        max = arm;
    }
    unknown_00 = max;
    unknown_0c = arm;
    unknown_18 = to;
    unknown_24 = Coord_Distance(from, to);
}
