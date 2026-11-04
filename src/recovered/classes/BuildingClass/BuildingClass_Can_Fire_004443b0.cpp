// Can_Fire: occupant, power, recharge and turret-facing checks.
#include "shared/building.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_slot218@TechnoClass@@=006c9260
// @ref ?Current@FacingClass@@=004b8be0

inline UnknownFacingDir Direction_Difference_004443b0(UnknownFacingDir const &current, UnknownFacingDir const &toward)
{
    return UnknownFacingDir((unsigned short)(current.Raw - toward.Raw));
}
inline bool Direction_Less_004443b0(UnknownFacingDir const &left, UnknownFacingDir const &right)
{
    return abs((short)left.Raw) < abs((short)right.Raw);
}

int BuildingClass::unknown_slot218(AbstractClass *target, int weapon, bool check_range)
{
    if (Type->CanBeOccupied && unknown_554.Count() == 0) return 5;
    if (Type->EMPulseCannon) return 6;
    if (!unknown_slot195()) return 6;
    if (unknown_5d8 != 0) return 3;
    int can_fire = TechnoClass::unknown_slot218(target, weapon, check_range);
    if (can_fire == 0 && unknown_slot232()) {
        UnknownFacingDir toward = unknown_slot285(target);
        int tolerance = Type->TurretAnimIsVoxel ? 0 : 8;
        if (Direction_Less_004443b0(UnknownFacingDir((unsigned short)(tolerance << 8)), Direction_Difference_004443b0(unknown_2e0.Current(), toward))) return 2;
    }
    return can_fire;
}
