// void PlanningNodeClass::Unknown_00615B60() -- 0x00615B60
// Purpose: appends this node to the static list unknown_list_00a76628 (0x00A76628; its growth
// path expanded from DynamicVectorClass::Add).
// Assumptions: the member's meaning (which planning state the list holds) is
// unidentified; no direct callers (the list globals are defined with the
// unit's header statics, HeaderStatics_diagonal_init_006101b0.cpp).
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_list_00a76628@PlanningNodeClass@@2V?$DynamicVectorClass@PAVPlanningNodeClass@@@@A=00a76628

// Only the members used here (as the header-statics source declares them).
class PlanningNodeClass {
public:
    void Unknown_00615B60();

    static DynamicVectorClass<PlanningNodeClass *> unknown_list_00a76628;   // 0x00A76628
};

void PlanningNodeClass::Unknown_00615B60()
{
    unknown_list_00a76628.Add(this);
}
