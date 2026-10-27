// void PlanningNodeClass::Unknown_006157C0() -- 0x006157C0
// Purpose: appends this node to the static list unknown_list_00a766d8 (0x00A766D8; its growth
// path expanded from DynamicVectorClass::Add).
// Assumptions: the member's meaning (which planning state the list holds) is
// unidentified; no direct callers (the list globals are defined with the
// unit's header statics, HeaderStatics_diagonal_init_006101b0.cpp).
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_list_00a766d8@PlanningNodeClass@@2V?$DynamicVectorClass@PAVPlanningNodeClass@@@@A=00a766d8

// Only the members used here (as the header-statics source declares them).
class PlanningNodeClass {
public:
    void Unknown_006157C0();

    static DynamicVectorClass<PlanningNodeClass *> unknown_list_00a766d8;   // 0x00A766D8
};

void PlanningNodeClass::Unknown_006157C0()
{
    unknown_list_00a766d8.Add(this);
}
