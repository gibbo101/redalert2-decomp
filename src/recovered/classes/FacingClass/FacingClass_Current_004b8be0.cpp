#include "shared/facing.hpp"
extern "C" int __cdecl abs(int value);
UnknownFacingDir FacingClass::Current() const
{
    if (Is_Rotating()) {
        short delta = (short)(Desired - Start);
        short ticks = (short)(abs(delta) / ROT);
        UnknownFacingDir result = *(UnknownFacingDir const *)&Desired;
        if (ticks > 0)
            result.Raw = (unsigned short)(result.Raw - (delta / ticks) * (short)Timer.Value());
        return result;
    }
    return *(UnknownFacingDir const *)&Desired;
}
