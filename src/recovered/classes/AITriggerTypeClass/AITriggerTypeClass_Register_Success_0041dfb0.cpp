// void AITriggerTypeClass::Register_Success() (0x0041DFB0)
// Raises the weight by the rules' success bonus plus a share for a better than
// even record (successes unknown_104 out of attempts unknown_108), clamped to
// MinWeight..MaxWeight, and counts the attempt and the success.
#include "shared/ai_trigger_type.hpp"
#include "shared/object.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3ffe8000000000000000=0079a728

void AITriggerTypeClass::Register_Success()
{
    double bonus = 0.0;
    if (unknown_108 > 0) {
        bonus = (unknown_104 / (double)unknown_108 - 0.5) * unknown_108;
        if (bonus < 0.0) {
            bonus = 0.0;
        }
    }
    Weight = Rules->unknown_b8 + Weight + bonus;
    if (Weight < MinWeight) {
        Weight = MinWeight;
    }
    if (Weight > MaxWeight) {
        Weight = MaxWeight;
    }
    unknown_104++;
    unknown_108++;
}
