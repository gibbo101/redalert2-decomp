#define RA2_COORD_EQUAL_MEMBER
// PlanningTokenClass *__fastcall Planning_New_Token(TechnoClass *techno) (0x00615820)
// Makes a techno's planning token, lists it and hands it to the techno.
#include "shared/planning.hpp"

PlanningTokenClass *__fastcall Planning_New_Token(TechnoClass *techno)
{
    PlanningTokenClass *token = new PlanningTokenClass(techno);
    PlanningTokenClass::unknown_list_00a76738.Add(token);
    techno->unknown_6d1420((UnknownTechno408 *)token);
    return token;
}
