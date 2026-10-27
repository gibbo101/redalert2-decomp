// MSShapeAnim::MSShapeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, bool unknown_34, int flags) (0x005AC6A0)
// Loads (or retrieves) the shape and plays all of its frames.
#include "shared/ms_anim.hpp"
// @ref ??_7MSShapeAnim@@6B@=007a6d64
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_load_shape_495310@@YIPAUShapeFileStruct@@ABVWstring@@PA_N@Z=00495310

MSShapeAnim::MSShapeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, bool unknown_34, int flags) :
    MSAnim(x, y),
    Drawer(drawer),
    unknown_24(unknown_24),
    Frame(0),
    unknown_34(unknown_34),
    Flags(flags),
    OwnsShape(false)
{
    Shape = unknown_load_shape_495310(filename, &OwnsShape);
    StartFrame = 0;
    EndFrame = Shape->FrameCount - 1;
}
