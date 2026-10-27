// void AITriggerTypeClass::Register_Failure() (0x0041E070)
// Changes the weight by the rules' failure value plus a scaled share for a
// worse than even record, clamped to MinWeight..MaxWeight, and counts the
// attempt.
#include "shared/ai_trigger_type.hpp"
#include "shared/object.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3ffe8000000000000000=0079a728

void AITriggerTypeClass::Register_Failure()
{
    double bonus = 0.0;
    if (unknown_108 > 0) {
        bonus = (unknown_104 / (double)unknown_108 - 0.5) * Rules->unknown_c8 * unknown_108;
        if (bonus > 0.0) {
            bonus = 0.0;
        }
    }
    Weight = Rules->unknown_c0 + Weight + bonus;
    if (Weight < MinWeight) {
        Weight = MinWeight;
    }
    if (Weight > MaxWeight) {
        Weight = MaxWeight;
    }
    unknown_108++;
}
