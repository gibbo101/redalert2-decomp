// bool BulletTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x00465180)
// Never places a bullet type directly (RA1: Create_And_Place).
#include "shared/bullet_type.hpp"

bool BulletTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    return false;
}
