// void LineTrail::Set_Decrement(int decrement) (0x00539510)
#include "shared/line_trail.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_a40b2c@@3HA=00a40b2c
// @ref ?unknown_a40b2c@@3HA=00a40b2c

void LineTrail::Set_Decrement(int decrement)
{
    if (!unknown_a40b2c) {
        decrement <<= 1;
    }
    Decrement = decrement;
}
