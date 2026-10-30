// void Unknown_0074dd00() (0x0074DD00)
// Ends dialog 0x12C (result 0) when it is open.
#include "shared/wol_sink.hpp"
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_007357E0@@YIXPAXH@Z=007357e0

void Unknown_0074dd00()
{
    void *dialog = Unknown_00735940(0x12C);
    if (dialog) Unknown_007357E0(dialog, 0);
}
