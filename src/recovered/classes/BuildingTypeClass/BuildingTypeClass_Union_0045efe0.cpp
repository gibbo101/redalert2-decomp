// Rect __fastcall Union<Rect>(Rect const &rect1, Rect const &rect2) (0x0045EFE0)
// The out-of-line instance of shared/rect.hpp's Union template (Westwood's
// wwlib Union): the smallest rectangle holding both valid rectangles; an
// invalid one yields the other. The cell and building code call it.
#include "shared/building_type.hpp"

template Rect const __fastcall Union(Rect const &rect1, Rect const &rect2);
