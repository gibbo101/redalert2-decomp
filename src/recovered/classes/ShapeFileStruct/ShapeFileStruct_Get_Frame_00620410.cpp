// Original00620410: frame-record lookup,27body bytes+5frozen NOPs.
// Existing owner/signature projection is replaced with the shared shape type;
// nominal name/const pointer remain source hypotheses, physical ABI verified.
#include "shared/rect.hpp"
// This provider does not use Get_Frame_Rect. Reuse a real original empty
// rectangle declaration rather than instantiate an unused header-static copy.
extern Rect const unknown_shape_empty_rect_84ed88;
#define SHAPE_FILE_EMPTY_RECT unknown_shape_empty_rect_84ed88
#define RA2_SHAPE_FRAME_SOURCE
#include "shared/shape_file.hpp"
ShapeFileFrameStruct const *ShapeFileStruct::Get_Frame(unsigned frame) const
{
    return frame < (unsigned)FrameCount ? &Frames[frame] : 0;
}
