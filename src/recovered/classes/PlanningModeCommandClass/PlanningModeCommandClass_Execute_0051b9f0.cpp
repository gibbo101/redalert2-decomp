// void PlanningModeCommandClass::Execute(int key) const -- 0x0051B9F0
// Planning mode off (0x006F64F0) with the 0x800 key bit, on (0x006F64D0) without.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/tab.hpp"
// @ref ?Unknown_006F64D0@@YIX_N@Z=006f64d0
// @ref ?Unknown_006F64F0@@YIX_N@Z=006f64f0

void PlanningModeCommandClass::Execute(int key) const
{
    if (key & 0x800) {
        Unknown_006F64F0(false);
    } else {
        Unknown_006F64D0(false);
    }
}
