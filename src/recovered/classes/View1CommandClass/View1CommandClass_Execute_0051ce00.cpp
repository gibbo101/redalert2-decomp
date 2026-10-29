// void View1CommandClass::Execute(int key) const -- 0x0051CE00
// Moves the tactical view to remembered view 1 (the scenario's Views[0]) at
// its ground height.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/id_source.hpp"
#include "shared/tactical.hpp"
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_006A66B0@Tactical@@QAEXABUCoordStruct@@@Z=006a66b0
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0

void View1CommandClass::Execute(int key) const
{
    CoordStruct coord(unknown_id_source_a3d290->Views[0].X * 256 + 128, unknown_id_source_a3d290->Views[0].Y * 256 + 128, 0);
    coord.Z = Map.Unknown_0055A280(coord);
    unknown_tactical_83996c->Unknown_006A66B0(coord);
    if (Map.unknown_11a4 != 0) {
        Map.Unknown_004994D0(unknown_geometry_k);
    }
}
