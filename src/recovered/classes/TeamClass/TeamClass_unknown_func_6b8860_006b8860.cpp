// Marks the team moving and "has been", clears under-strength, flags the members when reforming or forced active, restarts the script and completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Reset@ScriptClass@@QAE_NXZ=00668900

void TeamClass::unknown_func_6b8860()
{
    IsMoving = true;
    IsHasBeen = true;
    IsUnderStrength = false;
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (IsReforming || IsForcedActive) {
            member->unknown_579 = true;
        }
    }
    Script->Reset();
    StepCompleted = true;
}
