// void Tactical::Add_Shadow_Control(ShadowControlClass control) (0x006A7130): adds
// a heap copy of the control to the shadow controls (TibSun
// Tactical::Add_Shadow_Control).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
// @ref ?ShadowControls@TacticalLists@@2V?$DynamicVectorClass@PAVShadowControlClass@@@@A=00abe528

void Tactical::Add_Shadow_Control(ShadowControlClass control)
{
    ShadowControlClass *ctrl = new ShadowControlClass(control);
    TacticalLists::ShadowControls.Add(ctrl);
}
