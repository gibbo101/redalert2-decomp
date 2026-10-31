// void TeamClass::TMission_unknown_6bc5f0(ScriptMissionClass const &mission, bool unknown) (0x006BC5F0)
// Turns every TRUCKB unit of the team (the type is the TRUCKA one) and completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/techno_type.hpp"
// @ref ?From_Name@UnitTypeClass@@SIHPBD@Z=0070a890
// @ref __stricmp=00781f20
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ??_C@_06DJAP@TRUCKB?$AA@=007f6dbc
// @ref ??_C@_06MGLG@TRUCKA?$AA@=007f6db4

void TeamClass::TMission_unknown_6bc5f0(ScriptMissionClass const &mission, bool unknown)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (member->Kind_Of() == 1 && _stricmp(member->unknown_slot32()->ID, "TRUCKB") == 0) {
            ((UnitClass *)member)->Type = UnitTypes[UnitTypeClass::From_Name("TRUCKA")];
        }
    }
    StepCompleted = true;
}
