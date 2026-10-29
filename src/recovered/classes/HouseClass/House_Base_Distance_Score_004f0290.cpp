// int __fastcall House_Base_Distance_Score(HouseClass *, Cell const &, int, int) (0x004F0290)
// A placement score callback that HouseClass 0x004F03C0 calls for each
// candidate cell (BuildingClass 0x00440520 passes it): the score plus 1000
// per cell of the larger axis distance from the base plan's cell (+0x50 of
// the house's BaseClass). The fourth argument is unused. Name hypothesis.
#include "shared/house.hpp"
#include "shared/base.hpp"
#include "shared/crt_memory.hpp"

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

int __fastcall House_Base_Distance_Score(HouseClass *house, Cell const &cell, int score, int)
{
    int dx = cell.X - house->unknown_55f0.unknown_50.X;
    int dy = cell.Y - house->unknown_55f0.unknown_50.Y;
    return score + MAX(abs(dx), abs(dy)) * 1000;
}
