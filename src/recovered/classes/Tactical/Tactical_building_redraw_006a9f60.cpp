// void Tactical::Unknown_006A9F60(bool arg1, Rect const &rect1, Rect const &rect2) (0x006A9F60):
// the buildings of display layer 2 (+0x5B7 clear, or every one while the
// reload flag 0x00A40D13 is set) redrawn like 0x006A9E10's terrain objects,
// first object first (hypothesis).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/building_class.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?unknown_rect_839630@@3VRect@@A=00839630

void Tactical::Unknown_006A9F60(bool arg1, Rect const &rect1, Rect const &rect2)
{
    Rect clip = Intersect(rect1, rect2);
    for (int index = 0; index < DisplayClass::Layer[2].Count(); index++) {
        ObjectClass *object = DisplayClass::Layer[2][index];
        if (object->Kind_Of() == 6) {
            BuildingClass *building = (BuildingClass *)object;
            if (!building->unknown_5b7 || unknown_flag_a40d13) {
                Point2D offset(unknown_rect_839630.X, unknown_rect_839630.Y);
                Rect area = Offset_Rect(object->unknown_slot73(), offset.X, offset.Y);
                if (Rects_Overlap(area, clip)) {
                    Rect bounds = rect2;
                    object->unknown_slot63(&bounds, arg1, false);
                    object->unknown_75 = false;
                }
            }
        }
    }
}
