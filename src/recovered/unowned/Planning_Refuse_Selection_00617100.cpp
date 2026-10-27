#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Refuse_Selection(int kind) (0x00617100)
// Shows the refusal for a selection planning mode cannot take: aircraft (0),
// buildings (1) or unknown objects (2) (the values of Planning_Selection_Kind).
#include "shared/planning.hpp"
// @ref ??_C@_0BL@OMHN@MSG?3PlanningModeNoAircraft?$AA@=007ebed0
// @ref ??_C@_0BM@JDCL@MSG?3PlanningModeNoBuildings?$AA@=007ebeb4
// @ref ??_C@_0BL@CGPI@MSG?3PlanningModeNoUnknowns?$AA@=007ebe98

void __fastcall Planning_Refuse_Selection(int kind)
{
    if (kind == 0) {
        Planning_Refuse("MSG:PlanningModeNoAircraft");
    } else if (kind == 1) {
        Planning_Refuse("MSG:PlanningModeNoBuildings");
    } else if (kind == 2) {
        Planning_Refuse("MSG:PlanningModeNoUnknowns");
    }
}
