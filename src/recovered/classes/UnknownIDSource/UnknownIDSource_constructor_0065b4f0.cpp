// UnknownIDSource::UnknownIDSource() (0x0065B4F0)
// Builds the scenario: generator seeded with 0, timers stopped at zero,
// empty loadout lists growing by 10, the defaults (Set_Defaults), the special
// options, tech level 1, no campaign, names, briefing, waypoints, variables
// or views.
// @ref ??0?$VectorClass@PAVTechnoTypeClass@@@@QAE@IPBQAVTechnoTypeClass@@@Z=0046dbd0
// @ref ??0?$VectorClass@H@@QAE@IPBH@Z=0046d020
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Set_Defaults@UnknownIDSource@@QAEXXZ=0065b830
// @ref ?Init@SpecialClass@@QAEXXZ=0068b320
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/special.hpp"
#include "shared/tag.hpp"
#include "shared/abstract_type.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
#include "shared/type_list.hpp"

UnknownIDSource::UnknownIDSource()
{
    Set_Defaults();
    unknown_22fc = false;
    unknown_223b = false;
    Special().Init();
    TechLevel = 1;
    unknown_224c = -1;
    NextScenario[0] = '\0';
    AltNextScenario[0] = '\0';
    for (int index = 0; index < 101; index++) {
        Waypoints[index] = unknown_geometry_k;
    }
    wcscpy(Name, unknown_empty_wide_839d4c);
    strcpy(FileName, unknown_string_83c55c);
    strcpy(Briefing, unknown_string_83c55c);
    strcpy(UIName, unknown_string_83c55c);
    wcscpy(BriefingText, unknown_empty_wide_839d4c);
    for (int variable = 0; variable < 50; variable++) {
        Variables[variable].unknown_00[0] = '\0';
        unknown_6612c0(variable, false);
    }
    for (int local = 0; local < 50; local++) {
        LocalVariables[local].unknown_00[0] = '\0';
        unknown_661560(local, false);
    }
    memset(Views, 0, sizeof(Views));
}
