// FacingClass004B8B10, independent202+6. Both original epilogues return AL0/1.
// The existing void declaration was incomplete; proposed bool return/layout unchanged.
#include "shared/facing.hpp"
bool FacingClass::Set_Current(UnknownFacingDir const &dir)
{
    if(Current().Raw!=dir.Raw) {
        *(UnknownFacingDir *)&Desired=dir;
        *(UnknownFacingDir *)&Start=dir;
        Timer=CDTimerClass<FrameTimerClass>(0);
        return true;
    }
    Timer=CDTimerClass<FrameTimerClass>(0);
    return false;
}

// Existing real countdown helper; original call at004B8B23.
// @ref ?Value@?$CDTimerClass@VFrameTimerClass@@@@QBEJXZ=00453eb0
