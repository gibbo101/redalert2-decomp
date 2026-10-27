// Straw::Get_From (0x0069B050, virtual slot 1)
// Connects this straw to draw from straw (or disconnects with null). A
// straw already feeding another one is taken from it first.
#include "shared/straw.hpp"

void Straw::Get_From(Straw *straw)
{
    if (ChainTo != straw) {
        if (straw && straw->ChainFrom) {
            straw->ChainFrom->Get_From(0);
            straw->ChainFrom = 0;
        }
        if (ChainTo) {
            ChainTo->ChainFrom = 0;
        }
        ChainTo = straw;
        if (straw) {
            straw->ChainFrom = this;
        }
    }
}
