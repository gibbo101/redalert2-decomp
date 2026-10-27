// int BinkClass::Unknown_004303C0() (0x004303C0): milliseconds per frame.
#include "shared/movie.hpp"

int BinkClass::Unknown_004303C0()
{
    return 1000 / (Handle->FrameRate / Handle->FrameRateDiv);
}
