// int CellClass::unknown_47ce70() const (0x0047CE70): the radiation level
// (+0xF0) limited to Rules RadLevelMax, as an int.
#include "shared/cell.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

#define Min(a, b) ((a) < (b) ? (a) : (b))

int CellClass::unknown_47ce70() const
{
    return Min(unknown_f0, Rules->RadLevelMax);
}
