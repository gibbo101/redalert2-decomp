// Apparent speed while prone: two thirds for crawlers, 150% otherwise (0x00508980).
#include "shared/infantry.hpp"
// @ref ?unknown_slot303@FootClass@@UAEHXZ=004c9b10
int InfantryClass::unknown_slot303()
{
    int speed = FootClass::unknown_slot303();
    if (unknown_5c3) {
        if (Type->Crawls) {
            speed += speed / -3;
        } else {
            speed += speed / 2;
        }
    }
    return speed;
}
