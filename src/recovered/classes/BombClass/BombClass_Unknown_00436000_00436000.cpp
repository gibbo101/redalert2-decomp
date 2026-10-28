// int BombClass::Unknown_00436000() const (0x00436000): the frame of the
// bomb's flickering icon: two per sixth of IvanTimedDelay since it was
// planted, plus one in the second half of each IvanIconFlickerRate period,
// at most 11; 12 for a type 1 bomb.
#include "shared/object.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c

int BombClass::Unknown_00436000() const
{
    if (Type == 1) {
        return 12;
    }
    int rate = Rules->IvanIconFlickerRate;
    int frame = (Frame - unknown_34) / (Rules->IvanTimedDelay / 6) * 2;
    if (Frame % (rate * 2) >= rate) {
        frame++;
    }
    if (frame >= 12) {
        frame = 11;
    }
    return frame;
}
