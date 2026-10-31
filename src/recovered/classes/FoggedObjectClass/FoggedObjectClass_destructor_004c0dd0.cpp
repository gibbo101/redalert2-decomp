// FoggedObjectClass::~FoggedObjectClass() (0x004C0DD0)
// Leaves Array and Index (the inlined Remove_Index), clears the building-fog flags of the
// building in its cell and redraws the rectangle it covered.
#include "shared/fogged_object.hpp"
#include "shared/building_class.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
#include "shared/anim.hpp"
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$VectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11d0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Array@FoggedObjectClass@@2V?$DynamicVectorClass@PAVFoggedObjectClass@@@@A=00865e90
// @ref ?Index@FoggedObjectClass@@=00865e40
static inline Rect Offset_Rect(Rect rect, Point2D point)
{
    rect.X -= point.X;
    rect.Y -= point.Y;
    return rect;
}

FoggedObjectClass::~FoggedObjectClass()
{
    Array.Delete(this);
    Cell cell = XY_Cell(Coord.X / 256, Coord.Y / 256);
    int key = unknown_index_key(cell, unknown_30);
    Index.Remove_Index(key);
    if (unknown_30 == 6) {
        BuildingClass *building = (BuildingClass *)Map[cell].unknown_4717b0();
        if (building != 0) {
            building->unknown_5b7 = false;
            for (int index = 0; index < 18; index++) {
                if (building->unknown_454[index] != 0) {
                    ((AnimClass *)building->unknown_454[index])->unknown_179 = false;
                }
            }
        }
    }
    if (unknown_tactical_83996c != 0) {
        unknown_tactical_83996c->Register_Dirty_Area(Offset_Rect(unknown_40, unknown_tactical_83996c->unknown_b0), 0);
    }
}
