// RandomStraw::~RandomStraw() (0x0063D320)
// Clears the seed so no random state is left in memory.
#include "shared/random_straw.hpp"

RandomStraw::~RandomStraw()
{
    Reset();
}
