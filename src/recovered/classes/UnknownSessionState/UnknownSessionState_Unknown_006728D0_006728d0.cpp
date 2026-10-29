#include "shared/unknown_globals.hpp"
#include "shared/house_type.hpp"
#include "shared/id_source.hpp"

// Whether a session player's colour or one of the eight computer colours equals color; -2 (random) never is
// (expanded into 0x00672980).
bool UnknownSessionState::Unknown_006728D0(int color)
{
    if (color != -2) {
        int i;
        for (i = 0; i < Players.Count(); i++) {
            if (Players[i]->Get_Color_0066e2b0() == color) {
                return true;
            }
        }
        for (i = 0; i < 8; i++) {
            if (AIColor[i] == color) {
                return true;
            }
        }
    }
    return false;
}
