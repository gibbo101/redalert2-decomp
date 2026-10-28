// HRESULT Tactical::Load(IStream *) (0x006AC320): the base load, the
// placement NoInit constructor, the pointer table at +0xE4 swizzled, then the
// view position clamped (0x006A8C80) unless 0x00A40D13 is set and stored as
// both the current and the requested position.
#include "shared/tactical.hpp"
#include "shared/swizzle.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/vector_class.hpp"
// @ref ??0Tactical@@QAE@ABVNoInitClass@@@Z=006a26c0

HRESULT __stdcall Tactical::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) Tactical(NoInitClass());
        unknown_db0 = 0;
        for (int i = 0; i < unknown_e0; i++) {
            SwizzleManager.Swizzle((void **)&unknown_e4[i]);
        }
        Point2D point = unknown_d64;
        int x;
        int y;
        if (Unknown_006A8C80(&point) && !unknown_a40d13) {
            x = point.X;
            y = point.Y;
        } else {
            x = unknown_d64.X;
            y = unknown_d64.Y;
        }
        unknown_d64 = Point2D(x, y);
        unknown_d74 = Point2D(x, y);
        Unknown_006A9170();
        unknown_d7d = true;
        result = S_OK;
    }
    return result;
}
