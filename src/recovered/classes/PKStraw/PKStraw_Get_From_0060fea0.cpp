// PKStraw::Get_From(Straw *straw) (0x0060FEA0, virtual slot 1)
// Connects the input: the Blowfish stage draws from straw and this straw
// draws from the Blowfish stage. The source straw records this straw (not
// the Blowfish stage) as the one drawing from it.
#include "shared/pk_straw.hpp"

void PKStraw::Get_From(Straw *straw)
{
    if (BF.ChainTo != straw) {
        if (straw != 0 && straw->ChainFrom != 0) {
            straw->ChainFrom->Get_From(0);
            straw->ChainFrom = 0;
        }

        if (BF.ChainTo != 0) {
            BF.ChainTo->ChainFrom = 0;
        }

        BF.ChainTo = straw;
        BF.ChainFrom = this;
        ChainTo = &BF;
        if (straw != 0) {
            straw->ChainFrom = this;
        }
    }
}
