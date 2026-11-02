// int UnknownBulletData::Proximity_004ceee0(CoordStruct const &coord) (0x004CEEE0)
#include "shared/bullet.hpp"
#include "shared/unknown_geometry.hpp"

int UnknownBulletData::Proximity_004ceee0(CoordStruct const &coord)
{
    if (unknown_0c.Value() != 0) {
        return 0;
    }
    CoordStruct d = coord - unknown_18;
    int distance = (int)unknown_sqrt_4ba410((double)d.X * d.X + (double)d.Y * d.Y + (double)d.Z * d.Z) / 2;
    if (distance < 0x20) {
        return 1;
    }
    if (distance < 0x100 && distance > unknown_24) {
        return 2;
    }
    unknown_24 = distance;
    return 0;
}
