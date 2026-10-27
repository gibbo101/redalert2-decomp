#include "shared/cell.hpp"
// No-argument thiscall and one-pointer fastcall have the same observed ABI.
// The original helper at 0047CF10 returns CellClass+0x11B plus four
// when CellClass+0x140 bit 7 is set; its original member name is unknown.
// @ref ?Cell_Effective_Height_0047cf10@@=0047cf10
extern int __fastcall Cell_Effective_Height_0047cf10(CellClass const *cell);
int __fastcall Cell_Height_Transition_004bbe10(CellClass const *origin,
                                             CellClass const *nearby,
                                             CellClass const *destination)
{
    return Cell_Effective_Height_0047cf10(destination) - Cell_Effective_Height_0047cf10(nearby) >= 4
        && Cell_Effective_Height_0047cf10(destination) - Cell_Effective_Height_0047cf10(origin) > 0;
}
