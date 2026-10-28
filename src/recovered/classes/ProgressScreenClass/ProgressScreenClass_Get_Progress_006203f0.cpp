// double ProgressScreenClass::Get_Progress(int player) (0x006203F0)
// A player's share of the total (the total itself past the last player).
#include "shared/progress_screen.hpp"

double ProgressScreenClass::Get_Progress(int player)
{
    if (player >= Count) {
        return Total;
    }
    return Progress[player] / Total;
}
