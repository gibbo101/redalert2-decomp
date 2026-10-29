// void SetView3CommandClass::Execute(int key) const -- 0x0051D340
// Remembers the cell under the view position as view 3.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/id_source.hpp"
#include "shared/tactical.hpp"
// @ref ?Unknown_006A67D0@Tactical@@QAE?AUPoint2D@@XZ=006a67d0
// @ref ?Unknown_006A6BD0@Tactical@@QAE?AVCell@@ABUPoint2D@@@Z=006a6bd0

void SetView3CommandClass::Execute(int key) const
{
    Point2D point = unknown_tactical_83996c->Unknown_006A67D0();
    unknown_id_source_a3d290->Views[2] = unknown_tactical_83996c->Unknown_006A6BD0(point);
}
