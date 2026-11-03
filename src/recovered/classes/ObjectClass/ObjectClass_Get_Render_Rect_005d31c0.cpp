// ObjectClass::Get_Render_Rect (slot 73, 0x005D31C0; TibSun object.cpp): the screen rectangle the object's
// artwork covers, the union of the first frame and its shadow frame (frame + count / 2), plus a building's bib,
// centred on the object's render point.
#include "shared/techno.hpp"
#include "shared/building_type.hpp"
#include "shared/object_type.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref _unknown_static_rect=00a72ed0
// @ref ?Union@@YI?AVRect@@ABV1@0@Z=0045efe0

// Whether the object is a building (Kind_Of 6). The inline test at the bib, and the Point2D the result is
// built from, are the two /Ob2 sites after the first frame rectangle that keep its Rect constructor out of line.
static inline bool Object_Is_Building(ObjectClass const *object)
{
    return object->Kind_Of() == 6;
}

Rect ObjectClass::unknown_slot73()
{
    Point2D drawpoint;
    unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(), drawpoint);

    ShapeFileStruct const *sdata = (ShapeFileStruct const *)Class_Of()->unknown_slot39();
    if (sdata == 0) {
        return SHAPE_FILE_EMPTY_RECT;
    }
    int frame = 0;
    BuildingClass *bptr = (BuildingClass *)this;
    if (Kind_Of() == 6 && bptr->Type->FirestormWall) {
        frame = 15;
    }

    Rect rect1 = sdata->Get_Frame_Rect(frame);
    Rect rect2 = sdata->Get_Frame_Rect(frame + (sdata->Get_Count() / 2));

    int width = sdata->Get_Width();
    int height = sdata->Get_Height();

    Rect a = Union(rect1, rect2);

    if (Object_Is_Building(this) && bptr->Type->unknown_11cc) {
        Rect rect2 = ((ShapeFileStruct const *)bptr->Type->unknown_11cc)->Get_Frame_Rect(0);
        a = Union(a, rect2);
    }

    int x = drawpoint.X + a.X - width / 2;
    int y = drawpoint.Y + a.Y - height / 2;
    Point2D position(x, y);
    return Rect(position.X, position.Y, a.Width, a.Height);
}
