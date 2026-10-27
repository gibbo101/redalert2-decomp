// int TechnoClass::Unknown_006C22A0() (0x006C22A0)
// The production time (hypothesis: Westwood's Time_To_Build): the type's
// time (ObjectTypeClass slot 34) times the owner's multiplier for its kind,
// slowed by low power (LowPowerPenaltyModifier, clamped to
// MinLowPowerProductionSpeed / MaxLowPowerProductionSpeed), sped up by
// MultipleFactory for each extra factory, and scaled by
// WallBuildSpeedCoefficient for walls.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/aircraft.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_func_4f5a70@HouseClass@@QAEMPAVTechnoTypeClass@@@Z=004f5a70
// @ref ?Power_Fraction@HouseClass@@QBENXZ=004e8330
// @ref ?unknown_func_4eb980@HouseClass@@QAEHH_N@Z=004eb980
// @ref __real@4@3ff8a3d70a0000000000=007acfe0

int TechnoClass::Unknown_006C22A0()
{
    int time = Class_Of()->unknown_slot34();
    time = House->unknown_func_4f5a70(unknown_slot32()) * time;
    float power = House->Power_Fraction();
    float speed = 1.0f - (1.0f - power) * Rules->LowPowerPenaltyModifier;
    if ((double)Rules->MinLowPowerProductionSpeed >= speed) {
        speed = Rules->MinLowPowerProductionSpeed;
    }
    if (power < 1.0f && (double)Rules->MaxLowPowerProductionSpeed <= speed) {
        speed = Rules->MaxLowPowerProductionSpeed;
    }
    if (speed == 0.0f) {
        speed = 0.01f;
    }
    time = time / speed;
    bool naval = false;
    if (Kind_Of() == 1) {
        TechnoTypeClass *type = unknown_slot32();
        if (type != 0) {
            naval = type->Naval;
        }
    }
    int factories = House->unknown_func_4eb980(Kind_Of(), naval);
    float multiple = Rules->MultipleFactory;
    if (multiple > 0.0f) {
        for (int count = factories - 1; count > 0; count--) {
            time = time * multiple;
        }
    }
    if (Kind_Of() == 6 && ((BuildingClass *)this)->Type->Wall) {
        return time * Rules->WallBuildSpeedCoefficient;
    }
    return time;
}
