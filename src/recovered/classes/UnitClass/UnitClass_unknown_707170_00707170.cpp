// bool UnitClass::unknown_707170(TechnoClass *target) (0x00707170)
// Whether this unit may crush the target (hypothesis): a crusher (or ability
// 17), a target whose type is crushable, within the rules' +0x1390 distance;
// computer houses need AutoCrush or the rules' +0x142F; the owner is not in
// mode 2 and (human houses) is rich enough; the target must not refuse
// slot 49 for this owner.
#include "shared/unit.hpp"
#include "shared/fast_math.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910

// The distance between two coordinates (an inline helper; hypothesis).
static inline int Coord_Distance(CoordStruct const &a, CoordStruct const &b)
{
    CoordStruct delta(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    return (int)Fast_Sqrt((double)delta.X * delta.X + (double)delta.Z * delta.Z + (double)delta.Y * delta.Y);
}

bool UnitClass::unknown_707170(TechnoClass *target)
{
    if (!Type->Crusher && !unknown_6d7910(17)) {
        return false;
    }
    if (target && target->unknown_slot32()->unknown_1fd) {
        if (Coord_Distance(Center_Coord(), target->Center_Coord()) <= Rules->unknown_1390
            && (!House->Unknown_004F52F0() || Rules->unknown_142f || Type->AutoCrush)
            && House->unknown_c8 != 2
            && (House->Unknown_004F52F0() || House->unknown_194 >= Rules->unknown_10b0)) {
            if (target->unknown_slot49(House)) {
                return false;
            }
            return true;
        }
    }
    return false;
}
