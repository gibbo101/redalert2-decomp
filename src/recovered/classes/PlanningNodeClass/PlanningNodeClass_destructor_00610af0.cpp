#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass::~PlanningNodeClass() (0x00610AF0)
// Resets the node's branches and takes it out of the planning lists.
#include "shared/planning.hpp"
// @ref ?Delete@?$DynamicVectorClass@PAVPlanningNodeClass@@@@QAE_NH@Z=0061b350

PlanningNodeClass::~PlanningNodeClass()
{
    unknown_611ee0();
    Planning_Unlist_Node(this);
}
