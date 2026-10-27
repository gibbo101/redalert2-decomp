// GadgetClass::GadgetClass(int x, int y, int w, int h, unsigned flags, bool sticky) (0x004CEFE0)
// An unlinked gadget; a sticky one also reacts to left press and release.
#include "shared/gadget.hpp"
// @ref ??_7GadgetClass@@6B@=007a182c
// @ref ??_7LinkClass@@6B@=007a18b4
// @ref ?Flag_List_To_Redraw@GadgetClass@@UAEXXZ=0047d6f0
// @ref ?Get_ID@GadgetClass@@UBEIXZ=0049ecd0
// @ref ?Peer_To_Peer@GadgetClass@@UAEXIAAIAAVControlClass@@@Z=00483560
// @ref ?Is_To_Redraw@GadgetClass@@UAE_NXZ=0047d700

GadgetClass::GadgetClass(int x, int y, int w, int h, unsigned flags, bool sticky) :
    X(x),
    Y(y),
    Width(w),
    Height(h),
    IsToRepaint(false),
    IsSticky(sticky),
    IsDisabled(false),
    Flags(flags)
{
    if (IsSticky) {
        Flags |= LEFTPRESS | LEFTRELEASE;
    }
}
