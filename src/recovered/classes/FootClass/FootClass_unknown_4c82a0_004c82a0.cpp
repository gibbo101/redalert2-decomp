// int FootClass::unknown_4c82a0(AbstractClass *target) (0x004C82A0)
// How eagerly to attack a target: the negated rate (slot 168) for the
// current target; nothing for a cloaked current techno target, for a team
// that is not a base defense, in mission 10 or without a rate; otherwise
// the rate times 1024 divided by the frames needed to close the distance.
#include "shared/foot.hpp"
#include "shared/team_type.hpp"
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00

template <class T>
inline T Max_Of(T a, T b)
{
    return (a > b) ? a : b;
}

int FootClass::unknown_4c82a0(AbstractClass *target)
{
    if (target == 0) {
        return 0;
    }
    if (unknown_228 == target) {
        return -unknown_slot168();
    }
    if (unknown_228 != 0 && unknown_228->AbstractFlags.IsTechno && ((TechnoClass *)unknown_228)->unknown_slot163()) {
        return 0;
    }
    bool defense = (Team != 0 && Team->Class->IsBaseDefense) ? true : false;
    if (Team != 0 && !defense) {
        return 0;
    }
    if (unknown_slot91() == 10 || unknown_slot168() == 0) {
        return 0;
    }
    int range = unknown_5d4c00(target);
    int distance = range - unknown_slot85(0);
    int rate = unknown_slot168() << 10;
    if (distance > 0) {
        int speed = (unsigned)unknown_slot206() > 1 ? unknown_slot206() : 1;
        int steps = speed > 0 ? Max_Of(distance / speed, 1) : 1;
        rate = Max_Of(rate / steps, 1);
    }
    return rate;
}
