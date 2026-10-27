#include "shared/facing.hpp"
extern "C" int __cdecl abs(int value);
bool FacingClass::Set_Desired(UnknownFacingDir const &dir)
{
    if (Desired != (short)dir.Raw) {
    *(UnknownFacingDir *)&Start = Current();
    *(UnknownFacingDir *)&Desired = dir;
    if (ROT > 0) {
        short delta = (short)(Desired - Start);
        Timer = CDTimerClass<FrameTimerClass>(abs(delta) / ROT);
    }
    return true;
    }
    return false;
}
