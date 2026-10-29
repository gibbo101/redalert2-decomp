// void FollowCommandClass::Execute(int key) const -- 0x0051D4C0
// Follows the first selected object unless the view already follows one;
// stops following otherwise.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Unknown_0049EC40@DisplayClass@@QAEPAVObjectClass@@XZ=0049ec40
// @ref ?Unknown_0049EC60@DisplayClass@@QAEXPAVObjectClass@@@Z=0049ec60

void FollowCommandClass::Execute(int key) const
{
    if (unknown_objects_a40c60.Count() != 0 && Map.Unknown_0049EC40() == 0) {
        Map.Unknown_0049EC60(unknown_objects_a40c60[0]);
    } else {
        Map.Unknown_0049EC60(0);
    }
}
